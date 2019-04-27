//
// Created by chaed on 19. 2. 26.
//
#include <thread>

#include "ConnectingPlayerQueue.h"
#include "WaitingRoomManager.h"
#include "PlayerManager.h"
#include "GameInterface/Online/MessageType.h"
#include "GameInterface/Online/Packet.h"

using namespace server;
using namespace game_interface;

void ConnectingPlayerQueue::updateObserver(const game_interface::Packet& packet)
{
    if (exist(packet.getHeader().destId)) {
        auto ply = at(packet.getHeader().destId);
        detach(packet.getHeader().destId);

        PlayerManager::getInstance()->attach(ply);
        ply->updateObserver(packet);
    }
}

std::shared_ptr<ConnectingPlayerQueue> ConnectingPlayerQueue::getInstance()
{

    static auto inst = std::shared_ptr<ConnectingPlayerQueue>
            (&boost::serialization::singleton<ConnectingPlayerQueue>::get_mutable_instance());
    return inst;
}

void ConnectingPlayerQueue::boradcast(game_interface::Packet& packet)
{
    for (const auto& ply : getContainer()) {
        ply->sendPacket(packet);
    }
}

void ConnectingPlayerQueue::detach(ManagerInterface::unique_type unique)
{
    _Base::detach(unique);
}

void ConnectingPlayerQueue::postDetach(_Base::unique_type)
{}

void ConnectingPlayerQueue::postAttach(object_type player)
{
    player->sendUniqueInfo();
}

ManagerInterface::unique_type ConnectingPlayerQueue::findUser(ManagerInterface::unique_type)
{

}