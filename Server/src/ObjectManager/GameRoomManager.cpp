//
// Created by chaed on 19. 3. 20.
//


#include <string>

#include "GameInterface/include/PacketQueue.h"
#include "GameInterface/include/Packet.h"
#include "../../include/GameRoomManager.h"
#include "../../include/PlayerManager.h"

using namespace std;
using namespace server;
using namespace game_interface;

void GameRoomManager::postDetach(const unique_type unique)
{
}

void GameRoomManager::postAttach(const element_type& ply)
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