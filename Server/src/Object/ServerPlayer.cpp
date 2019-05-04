//
// Created by chaed on 19. 2. 22.
//

#include "GameInterface/include/Packet.h"
#include "GameInterface/include/PacketQueue.h"

#include "../../include/ServerPlayer.h"
#include "../../include/WaitingRoomManager.h"
#include "../../include/PlayerManager.h"

using namespace std;
using namespace server;
using namespace game_interface;
using namespace tetris_module;

ServerPlayer::ServerPlayer()
{}

void ServerPlayer::updateObserver(const game_interface::Packet& packet)
{
    switch (packet.getHeader().message) {
        case messageInfo::PLAYER_INIT_INFO:
            recvInitInfo(packet);
            break;
    }
}

void ServerPlayer::sendPacket(const Packet& packet) const
{
    packet.updateTime();

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

void ServerPlayer::enterRoom(const size_t order)
{
    if (m_ctl != nullptr) {
        assert(0);
        return;
    }

    m_ctl = unique_ptr<tetris_module::TFigureController>(new tetris_module::TFigureController(
            static_cast<int>( order)));
    //m_ctl = make_unique<TFigureController>(order);
}

