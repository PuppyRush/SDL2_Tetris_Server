//
// Created by chaed on 19. 2. 6.
//

#ifndef SDL2_TETRIS_SERVER_SERVER_H
#define SDL2_TETRIS_SERVER_SERVER_H

#pragma  once

#include <atomic>
#include <memory>

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Acceptor.h>
#include  <ace/SOCK_Stream.h>
#include  <ace/INET_Addr.h>
#include  <ace/Message_Queue.h>
#include  <ace/Synch.h>

#include "Tetris/include/TFigureController.h"
#include "GameInterface/include/Type.h"

namespace server {

class PlayerService : public ACE_Event_Handler
{

public:
    PlayerService(ACE_SOCK_Acceptor& acceptor, ACE_Reactor* reactor);

    ~PlayerService(void);

    virtual ACE_HANDLE get_handle(void) const;

    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    int send(void* data, game_interface::t_ssize len) const;

    game_interface::t_unique unique;

private:
    ACE_SOCK_Stream peer_;
    ACE_INET_Addr addr_;
    ACE_Message_Queue<ACE_MT_SYNCH> send_datas_;
    std::unique_ptr<tetris_module::TFigureController> m_figureCtl;
};

}

#endif //SDL2_TETRIS_SERVER_SERVER_H
