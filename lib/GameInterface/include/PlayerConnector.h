//
// Created by kim on 19. 1. 10.
//

#ifndef SDLTETRIS_TCLIENT_TCLIENTCONNECTOR_H
#define SDLTETRIS_TCLIENT_TCLIENTCONNECTOR_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <memory>

#include  <ace/Event_Handler.h>
#include  <ace/Reactor.h>
#include  <ace/SOCK_Connector.h>
#include <ace/Init_ACE.h>

#include  "ClientService.h"
#include "GameInterface/include/TStruct.h"

namespace game_interface {

class PlayerConnector : public ACE_Event_Handler
{

public:
    PlayerConnector(const char* ipstr, ACE_Reactor* reactor, ClientService& stream);

    virtual ~PlayerConnector(void);

    void connect();

    inline const bool isConnection() const noexcept
    { return m_isConnection; }

    virtual ACE_HANDLE get_handle(void) const;

    //접속  이벤트
    virtual int handle_input(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_output(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_exception(ACE_HANDLE fd = ACE_INVALID_HANDLE);

    virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

private:
    std::string m_ipstring;
    int m_isConnection;
    ACE_SOCK_Connector m_connector;
    ClientService& m_stream;
};

}

#endif //SIMPLE_ECHOCLIENT_GCONNECTOR_H
