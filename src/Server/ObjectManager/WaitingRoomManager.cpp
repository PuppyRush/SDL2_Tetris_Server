//
// Created by chaed on 19. 2. 24.
//

#include <string>

#include "WaitingRoomManager.h"
#include "GameInterface/Online/PacketQueue.h"
#include "GameInterface/Online/Packet.h"
#include "PlayerManager.h"

using namespace std;
using namespace server;
using namespace game_interface;

void WaitingRoomManager::postDetach(_Base::unique_type obs)
{
}

void WaitingRoomManager::postAttach(object_type obs)
{
    sendCreateWaitingRoom(obs);
}

void WaitingRoomManager::updateObserver(const game_interface::Packet& packet)
{
    if (exist(packet.getHeader().destId)) {
        at(packet.getHeader().destId)->updateObserver(packet);
    }

    switch (packet.getHeader().message) {
        case messageInfo::WAITINGROOMS_REQUEST_INIT_INFO:
            sendInitInfo(packet);
            break;

        default:
            break;
    }
}

void WaitingRoomManager::sendInitInfo(const game_interface::Packet& packet)
{
    if (!PlayerManager::getInstance()->exist(packet.getHeader().senderId)) {
        return;
    }

    auto destPlayer = PlayerManager::getInstance()->at(packet.getHeader().senderId);
    for (const auto& wroom : getContainer()) {
        Packet _packet{{destPlayer->getUnique(), wroom->getUnique(), messageInfo::WAITINGROOMS_RESPONSE_INIT_INFO},
                       wroom->toJson()};
        destPlayer->sendPacket(_packet);
    }
}

void WaitingRoomManager::sendCreateWaitingRoom(object_type obj)
{

}

void WaitingRoomManager::boradcast(game_interface::Packet& packet)
{
    for (const auto& wroom : getContainer()) {
        //ply->sendPacket(packet);
    }
}

void WaitingRoomManager::detach(ManagerInterface::unique_type unique)
{
    _Base::detach(unique);
}

void WaitingRoomManager::exitUserFromWaitingRoom(_Base::unique_type unique)
{
    for (const auto& wroom : getContainer()) {
        wroom->exit(unique);
    }
}

ManagerInterface::unique_type WaitingRoomManager::findUser(ManagerInterface::unique_type)
{
}