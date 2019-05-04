//
// Created by chaed on 19. 2. 6.
//

#ifndef SDL2_TETRIS_SERVER_SERVERACCEPTOR_H
#define SDL2_TETRIS_SERVER_SERVERACCEPTOR_H

#pragma  once

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Acceptor.h>

namespace server {

class ServerAcceptor : public ACE_Event_Handler
{
private:
    ACE_SOCK_Acceptor acceptor_;

public:
    ServerAcceptor(const char* ipstr, ACE_Reactor* reactor);

    ~ServerAcceptor(void);

    virtual ACE_HANDLE get_handle(void) const;

    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
};

}

#endif //SDL2_TETRIS_SERVER_SERVERACCEPTOR_H
