//
// Created by chaed on 19. 2. 6.
//

#include  <iostream>

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Acceptor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/INET_Addr.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>
#include  <ace/OS.h>

#include "GameInterface/include/PacketQueue.h"

#include "../include/PlayerService.h"
#include "../include/PlayerManager.h"
#include "../include/ConnectingPlayerQueue.h"

using namespace server;
using namespace game_interface;
using namespace game_interface::packet;

PlayerService::PlayerService(ACE_SOCK_Acceptor& acceptor, ACE_Reactor* reactor)
        : ACE_Event_Handler(reactor), peer_(ACE_INVALID_HANDLE)
{
    if (-1 == acceptor.accept(peer_, &addr_)) {
        delete this;
        return;
    }

    char addr_string[256];
    addr_.addr_to_string(addr_string, 256);
    std::cout << std::endl << "Enter Client:" << addr_string << std::endl;

    this->reactor()->register_handler(this, ACE_Event_Handler::READ_MASK);

}

PlayerService::~PlayerService(void)
{
}

ACE_HANDLE
PlayerService::get_handle(void) const
{
    return this->peer_.get_handle();
}

int
PlayerService::handle_input(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    const int BUF = 1024;
    unsigned char in[BUF];

    ACE_Time_Value vt(0, 0);

    const t_ssize len = this->peer_.recv(in, BUF, &vt);
    if (len <= 0) {//클라이언트  종료. 통신  에러
        return -1;
    }

    ACE_Message_Block* mb = new ACE_Message_Block(len);
    ACE_OS::memcpy(mb->wr_ptr(), in, len);
    mb->wr_ptr(len);
    send_datas_.enqueue_tail(mb);

    this->reactor()->register_handler(this, ACE_Event_Handler::WRITE_MASK);

    Packet p{in, static_cast<game_interface::t_ssize>(len)};
    game_interface::PacketQueue::getInstance().pushEvent(p);
    return 0;
}

int
PlayerService::send(void* data, t_ssize len) const
{
    peer_.send(data, len);
    return 0;
}

int
PlayerService::handle_output(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{
    ACE_Message_Block* mb(NULL);
    ACE_Time_Value rt(0, 0);
    do {
        this->send_datas_.dequeue_head(mb, &rt);

        t_ssize len = this->peer_.send(mb->rd_ptr(), mb->length(), &rt);
        if (len < 0) {//통신  에러
            mb->release();
            return -1;
        }

        mb->rd_ptr(len);
        if (mb->length() > 0) {
            this->send_datas_.enqueue_head(mb);
            break;
        }
        mb->release();
    } while (false);

    if (this->send_datas_.is_empty()) {
        ACE_Reactor_Mask m = ACE_Event_Handler::WRITE_MASK | ACE_Event_Handler::DONT_CALL;
        this->reactor()->remove_handler(this, m);
    }
    return 0;
}

int
PlayerService::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
    char addr_string[256];
    addr_.addr_to_string(addr_string, 256);
    std::cout << std::endl << "Exit Client:" << addr_string << std::endl;

    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    this->send_datas_.flush();
    this->peer_.close();

    if (ConnectingPlayerQueue::getInstance()->exist(unique)) {
        ConnectingPlayerQueue::getInstance()->detach(unique);
    }
    if (PlayerManager::getInstance()->exist(unique)) {
        PlayerManager::getInstance()->detach(unique);
    }

    //delete  this;
    return 0;
}
