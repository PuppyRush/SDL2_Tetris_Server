//
// Created by chaed on 19. 2. 22.
//

#include "ServerPlayer.h"
#include "GameInterface/Online/Packet.h"
#include "GameInterface/Online/PacketQueue.h"
#include "../ObjectManager/WaitingRoomManager.h"
#include "../ObjectManager/PlayerManager.h"

using namespace server;
using namespace game_interface;

void ServerPlayer::updateObserver(const game_interface::Packet& packet)
{
    switch (packet.getHeader().message) {
        case messageInfo::PLAYER_INIT_INFO:
            recvInitInfo(packet);
            break;
    }
}

void ServerPlayer::sendPacket(Packet& packet)
{
    packet.setHeader().timestamp = std::time(nullptr);
    packet.setHeader().where = messageDirection::SERVER;

    printf("server send : %d %d %dl\n", packet.getHeader().senderId, toUType(packet.getHeader().message),
           packet.getHeader().timestamp);

    auto bytes = packet.toByte();
    m_service->send((void*)bytes.first, bytes.second);
}

void ServerPlayer::sendUniqueInfo()
{
    Json::Value json;
    json["unique"] = static_cast<int>( this->getUnique());

    Packet packet{{NULL_ID, getUnique(), messageInfo::PLAYER_INIT_INFO}, json};
    sendPacket(packet);
}

void ServerPlayer::recvInitInfo(const game_interface::Packet packet)
{
    const auto& json = packet.getPayload();
    fromJson(json);
}

void ServerPlayer::disconnection()
{

}

Json::Value ServerPlayer::toJson() const
{
    return Player::toJson();
}

void ServerPlayer::fromJson(const Json::Value& json)
{
    Player::fromJson(json);
}