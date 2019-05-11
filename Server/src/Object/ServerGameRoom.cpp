//
// Created by chaed on 19. 3. 6.
//
#include <string>

#include "../../include/PlayerManager.h"
#include "../../include/ServerGameRoom.h"
#include "../../include/ServerPlayer.h"

using namespace std;
using namespace server;
using namespace game_interface;
using namespace game_interface::packet;

void ServerGameRoom::updateObserver(const Packet& packet)
{
    switch (packet.getHeader().message) {
        case messageInfo::GAME_REQUEST_BOARDINFO:
            responseGameBoardInfo(packet);
            break;
    }

}

void ServerGameRoom::responseGameBoardInfo(const Packet& packet)
{

    for (const auto& ply : getPlayerContainer()) {
        Packet copied{packet};
        copied.setDestId(ply->getUnique());
        copied.setSenderId(this->getUnique());
        copied.setMessage(messageInfo::GAME_RESPONSE_BOARDINFO);
        ply->sendPacket(copied);
    }
}

void ServerGameRoom::fromJson(const Json::Value& json)
{
    GameRoom::fromJson(json);

    auto playerManager = PlayerManager::getInstance();

    const size_t player_count = json["player_count"].asUInt();
    const auto playerJs = json[NAME_PLAYER.data()];
    for (int i = 0; i < player_count; i++) {
        const auto player = playerJs[i];
        const t_id unique = player["unique"].asUInt64();

        if (playerManager->exist(unique) && !exist(unique)) {
            enter(playerManager->at(unique));
        }
    }
}

Json::Value ServerGameRoom::toJson() const
{
    return GameRoom::toJson();
}

void ServerGameRoom::postEnter(const player_ptr& ply)
{

}

void ServerGameRoom::postExit(const player_ptr& ply)
{

}