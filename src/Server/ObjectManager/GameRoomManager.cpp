//
// Created by chaed on 19. 3. 20.
//


#include <string>

#include "GameRoomManager.h"
#include "GameInterface/Online/PacketQueue.h"
#include "GameInterface/Online/Packet.h"
#include "PlayerManager.h"

using namespace std;
using namespace server;
using namespace game_interface;

void GameRoomManager::postDetach(_Base::unique_type obs)
{
}

void GameRoomManager::postAttach(object_type obs)
{
}

void GameRoomManager::updateObserver(const game_interface::Packet& packet)
{
    if (exist(packet.getHeader().destId)) {
        at(packet.getHeader().destId)->updateObserver(packet);
    }

    switch (packet.getHeader().message) {
    }
}

void GameRoomManager::boradcast(game_interface::Packet& packet)
{
    for (const auto& groom : getContainer()) {
        //ply->sendPacket(packet);
    }
}

void GameRoomManager::detach(ManagerInterface::unique_type unique)
{
    _Base::detach(unique);
}

ManagerInterface::unique_type GameRoomManager::findUser(ManagerInterface::unique_type)
{

}