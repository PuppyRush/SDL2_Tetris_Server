//
// Created by chaed on 19. 2. 24.
//

#include <string>

#include "GameInterface/include/Packet.h"
#include "GameInterface/include/PacketQueue.h"
#include "../../include/PlayerManager.h"
#include "../../include/WaitingRoomManager.h"
#include "../../include/GameRoomManager.h"

using namespace std;
using namespace server;
using namespace game_interface;
using namespace game_interface::packet;

void PlayerManager::postDetach(const unique_type unique)
{
    WaitingRoomManager::getInstance()->exitUserFromWaitingRoom(unique);
}

void PlayerManager::postAttach(const element_type& ply)
{
    if (WaitingRoomManager::getInstance()->getContainer().empty()) {
        assert(0);
    } else {
        WaitingRoomManager::getInstance()->getContainer().begin()->get()->enter(ply);
    }
}

void PlayerManager::updateObserver(const Packet& packet)
{
    if (exist(packet.getHeader().destId)) {
        at(packet.getHeader().destId)->updateObserver(packet);
    }
}

void PlayerManager::boradcast(Packet& packet)
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
    return 0;
}
