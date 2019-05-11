//
// Created by chaed on 19. 2. 26.
//
#include <thread>

#include "GameInterface/include/MessageType.h"
#include "GameInterface/include/Packet.h"

#include "../../include/ConnectingPlayerQueue.h"
#include "../../include/WaitingRoomManager.h"
#include "../../include/PlayerManager.h"

using namespace server;
using namespace game_interface;
using namespace game_interface::packet;

void ConnectingPlayerQueue::updateObserver(const Packet& packet)
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

void ConnectingPlayerQueue::boradcast(Packet& packet)
{
    for (const auto& ply : getContainer()) {
        ply->sendPacket(packet);
    }
}

void ConnectingPlayerQueue::detach(ManagerInterface::unique_type unique)
{
    _Base::detach(unique);
}

void ConnectingPlayerQueue::postDetach(const unique_type unique)
{}

void ConnectingPlayerQueue::postAttach(const element_type& element)
{
    element->sendUniqueInfo();
}

ManagerInterface::unique_type ConnectingPlayerQueue::findUser(ManagerInterface::unique_type)
{

}