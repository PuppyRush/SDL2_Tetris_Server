//
// Created by chaed on 19. 2. 24.
//

#include <string>

#include "GameInterface/include/PacketQueue.h"
#include "GameInterface/include/Packet.h"
#include "../../include/WaitingRoomManager.h"
#include "../../include/PlayerManager.h"

using namespace std;
using namespace server;
using namespace game_interface;
using namespace game_interface::packet;

void WaitingRoomManager::postDetach(const unique_type unique)
{
}

void WaitingRoomManager::postAttach(const element_type& element)
{
    sendCreateWaitingRoom(element);
}

void WaitingRoomManager::updateObserver(const Packet& packet)
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

void WaitingRoomManager::sendInitInfo(const Packet& packet)
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

void WaitingRoomManager::sendCreateWaitingRoom(element_type obj)
{

}

void WaitingRoomManager::boradcast(Packet& packet)
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