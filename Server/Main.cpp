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

void fn(ACE_Reactor* app)
{
    app->run_reactor_event_loop();
}

int main(int argc, char* argv[])
{
    using namespace server;
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
    new server::ServerAcceptor("127.0.0.1:12345", &reactor);

    std::thread t1(fn, &reactor);

    t1.join();

    ACE::fini();
    return 0;
}