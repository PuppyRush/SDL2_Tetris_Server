//
// Created by chaed on 19. 2. 6.
//

#include  <iostream>
#include  <ace/INET_Addr.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <netdb.h>

#include "GameInterface/include/PacketQueue.h"

#include "../include/ServerAcceptor.h"
#include "../include/PlayerService.h"
#include "../include/ServerPlayer.h"
#include "../include/ConnectingPlayerQueue.h"
#include "../include/WaitingRoomManager.h"

using namespace server;

ServerAcceptor::ServerAcceptor(std::string ip, ACE_Reactor* reactor)
        : ACE_Event_Handler(reactor)
{
    ACE_INET_Addr addr(ip.c_str());

    int bret = acceptor_.open(addr, 1);
    if (-1 == bret) {
        std::cout << std::endl << "Listen fail:" << ip << std::endl;
        delete this;
        return;
    }

    std::cout << std::endl << "Server start:" << ip << std::endl;

    this->reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
}

ServerAcceptor::~ServerAcceptor(void)
{
}

ACE_HANDLE
ServerAcceptor::get_handle(void) const
{
    return this->acceptor_.get_handle();
}

int
ServerAcceptor::handle_input(ACE_HANDLE fd/* = ACE_INVALID_HANDLE*/)
{

    auto ps = new PlayerService{this->acceptor_, this->reactor()};

    auto player = std::make_shared<ServerPlayer>();
    player->m_service = std::shared_ptr<PlayerService>(ps);
    player->m_service->unique = player->getUnique();

    ConnectingPlayerQueue::getInstance()->attach(player);

    return 0;
}

int
ServerAcceptor::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
    ACE_Reactor_Mask m = ACE_Event_Handler::ALL_EVENTS_MASK | ACE_Event_Handler::DONT_CALL;
    this->reactor()->remove_handler(this, m);
    this->acceptor_.close();
    delete this;
    return 0;
}

