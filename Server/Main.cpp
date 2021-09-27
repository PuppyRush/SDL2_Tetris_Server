//
// Created by chaed on 19. 2. 6.
//
#include <cstdio>
#include  <thread>

#include <ace/SOCK_Acceptor.h>
#include <ace/Log_Msg.h>
#include  <ace/ACE.h>
#include  <ace/TP_Reactor.h>
#include  <ace/Reactor.h>
#include <ace/Init_ACE.h>



#include "include/PlayerService.h"
#include "include/ServerAcceptor.h"
#include "include/Quit.h"
#include "include/ServerWaitingRoom.h"
#include "include/WaitingRoomManager.h"
#include "include/PlayerManager.h"
#include "include/ConnectingPlayerQueue.h"
#include "include/GameRoomManager.h"
#include "GameInterface/include/ManagerController.h"
#include "GameInterface/include/Initiator.h"
#include "GameInterface/include/TStruct.h"

//Example: b1 == 192, b2 == 168, b3 == 0, b4 == 100
struct IPv4
{
    unsigned char b1=127, b2=0, b3=0, b4=1;
};

bool getMyIP(IPv4& myIP)
{
    char szBuffer[1024];

#ifdef WIN32
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if (::WSAStartup(wVersionRequested, &wsaData) != 0)
        return false;
#endif


    if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
    {
#ifdef WIN32
        WSACleanup();
#endif
        return false;
    }

    struct hostent* host = gethostbyname(szBuffer);
    if (host == NULL)
    {
#ifdef WIN32
        WSACleanup();
#endif
        return false;
    }

    //Obtain the computer's IP
    myIP.b1 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b1;
    myIP.b2 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b2;
    myIP.b3 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b3;
    myIP.b4 = ((struct in_addr*)(host->h_addr))->S_un.S_un_b.s_b4;

#ifdef WIN32
    WSACleanup();
#endif
    return true;
}

void fn(ACE_Reactor* app)
{
    app->run_reactor_event_loop();
}

#undef main

int main(int argc, char** argv)
{
    using namespace server;
    using namespace game_interface;
    game_interface::GameInterface_Init(true);

    auto& mngCtl = game_interface::ManagerController::getInstance();
    mngCtl.attach(WaitingRoomManager::getInstance());
    mngCtl.attach(PlayerManager::getInstance());
    mngCtl.attach(ConnectingPlayerQueue::getInstance());
    mngCtl.attach(GameRoomManager::getInstance());
     
    auto wroom = std::make_shared<server::ServerWaitingRoom>();
    wroom->setRoomName("Werlcome to TetrisWorld");
    WaitingRoomManager::getInstance()->attach(wroom);

    ACE::init();
    ACE_TP_Reactor tp;
    ACE_Reactor reactor(&tp);

    new server::Quit(&reactor);

    IPv4 ipv4;
    getMyIP(ipv4);
    TIPString ipstring{ {ipv4.b1, ipv4.b2, ipv4.b3, ipv4.b4}, 12345 };
    new server::ServerAcceptor(ipstring.getIpAndPortString(), &reactor);

    std::thread t1(fn, &reactor);

    t1.join();

    ACE::fini();
    return 0;
}