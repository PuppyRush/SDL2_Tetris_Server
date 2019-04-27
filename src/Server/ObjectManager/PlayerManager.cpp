//
// Created by chaed on 19. 2. 24.
//

#include <string>

#include "PlayerManager.h"
#include "GameInterface/Online/Packet.h"
#include "GameInterface/Online/PacketQueue.h"
#include "WaitingRoomManager.h"
#include "GameRoomManager.h"

using namespace std;
using namespace server;
using namespace game_interface;

void PlayerManager::postDetach(_Base::unique_type unique)
{
    WaitingRoomManager::getInstance()->exitUserFromWaitingRoom(unique);
}

void PlayerManager::postAttach(object_type obs)
{
    if (WaitingRoomManager::getInstance()->getContainer().empty()) {
        assert(0);
    } else {
        WaitingRoomManager::getInstance()->getContainer().begin()->get()->enter(obs);
    }
}

void PlayerManager::updateObserver(const game_interface::Packet& packet)
{
    if (exist(packet.getHeader().destId)) {
        at(packet.getHeader().destId)->updateObserver(packet);
    }
}

void PlayerManager::boradcast(game_interface::Packet& packet)
{
    for (const auto& ply : getContainer()) {
        ply.second->sendPacket(packet);
    }
}

void PlayerManager::detach(ManagerInterface::unique_type unique)
{
    _Base::detach(unique);
}

ManagerInterface::unique_type PlayerManager::findUser(ManagerInterface::unique_type)
{

}
