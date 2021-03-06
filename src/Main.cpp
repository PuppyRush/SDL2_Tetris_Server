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

#include "Server/PlayerService.h"
#include "Server/ServerAcceptor.h"
#include "Server/Quit.h"
#include "Server/Object/ServerWaitingRoom.h"
#include "Server/ObjectManager/WaitingRoomManager.h"
#include "Server/ObjectManager/PlayerManager.h"
#include "Server/ObjectManager/ConnectingPlayerQueue.h"
#include "Server/ObjectManager/GameRoomManager.h"
#include "GameInterface/SubScription/ManagerController.h"

void fn(ACE_Reactor* app)
{
    app->run_reactor_event_loop();
}

int main(int argc, char* argv[])
{

    using namespace server;

    game_interface::PacketQueue::getInstance().setServer(true);
    game_interface::PacketQueue::getInstance().run();

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