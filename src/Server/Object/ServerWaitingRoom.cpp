//
// Created by chaed on 19. 2. 22.
//

#include <string>

#include "ServerWaitingRoom.h"
#include "GameInterface/Online/MessageType.h"

#include "../ObjectManager/PlayerManager.h"
#include "../ObjectManager/GameRoomManager.h"
#include "../ObjectManager/PlayerManager.h"

using namespace std;
using namespace server;
using namespace game_interface;

void ServerWaitingRoom::enter(player_ptr ply)
{
    WaitingRoom::enter(ply);
}

void ServerWaitingRoom::exit(const unique_type unique)
{
    WaitingRoom::exit(unique);
}

void ServerWaitingRoom::postEnter(player_ptr ply)
{

}

void ServerWaitingRoom::postExit(const unique_type unique)
{
    GameRoomManager::getInstance()->exist(unique);
}

void ServerWaitingRoom::addGameRoom(Room::room_ptr room)
{
    WaitingRoom::addGameRoom(room);
}

void ServerWaitingRoom::removeGameRoom(const Room::unique_type unique)
{
    WaitingRoom::removeGameRoom(unique);
}

void ServerWaitingRoom::postAddedGameRoom(room_ptr room)
{

}

void ServerWaitingRoom::postRemovedGameRoom(const unique_type unique)
{

}

void ServerWaitingRoom::updateObserver(const game_interface::Packet& packet)
{
    switch (packet.getHeader().message) {
        case messageInfo::WAITINGROOMS_REQUEST_ENTER:
            recvRequestEnter(packet);
            break;
        case messageInfo::WAITINGROOMS_REQUEST_CREATE:
            recvRequestCreate(packet);
            break;
        case messageInfo::WAITINGROOMS_SEND_CHAT:
            broadcastChat(packet);
            break;
    }
}

void ServerWaitingRoom::broadcastChat(const game_interface::Packet& packet)
{
    Packet& chatPacket = const_cast<Packet&>(packet);

    chatPacket.setHeader().senderId = getUnique();
    chatPacket.setHeader().destId = getUnique();
    chatPacket.setHeader().message = messageInfo::WAITINGROOMS_RECV_CHAT;

    broadcast(chatPacket);
}

void ServerWaitingRoom::recvRequestEnter(const game_interface::Packet& packet)
{

}

void ServerWaitingRoom::recvRequestCreate(const game_interface::Packet& packet)
{
    const auto json = packet.getPayload();

    if (!PlayerManager::getInstance()->exist(packet.getHeader().senderId)) {
        assert(0);
    }

    auto player = PlayerManager::getInstance()->at(packet.getHeader().senderId);

    auto gameroom = make_shared<ServerGameRoom>();
    gameroom->setRoomName(json["name"].asString());

    gameroom->enter(player);
    addGameRoom(gameroom);
    GameRoomManager::getInstance()->attach(gameroom);

    exit(player->getUnique());

    auto gameroomJson = gameroom->toJson();
    Packet pk{{player->getUnique(), gameroom->getUnique(), messageInfo::WAITINGROOMS_RESPONSE_CREATE}, gameroomJson};
    player->sendPacket(pk);
}

void ServerWaitingRoom::broadcast(game_interface::Packet& packet)
{
    for (auto& ply : getPlayerContainer()) {
        ply->sendPacket(packet);
    }
}

Json::Value ServerWaitingRoom::toJson() const
{
    return WaitingRoom::toJson();
}

void ServerWaitingRoom::fromJson(const Json::Value& json)
{
    WaitingRoom::fromJson(json);

    auto playerManager = PlayerManager::getInstance();

    const size_t player_count = json["player_count"].asUInt();
    const auto playerJs = json[NAME_PLAYER.data()];
    for (int i = 0; i < player_count; i++) {
        const auto player = playerJs[i];
        const auto unique = player["unique"].asUInt64();

        if (playerManager->exist(unique) && !exist(unique)) {
            enter(playerManager->at(unique));
        }
    }

    auto roomManager = GameRoomManager::getInstance();
    const size_t gameroom_count = json["gameroom_count"].asUInt();
    const auto roomJs = json[NAME_GAMEROOM.data()];
    for (int i = 0; i < gameroom_count; i++) {
        const auto room = roomJs[i];
        const auto unique = room["unique"].asUInt64();

        if (roomManager->exist(unique) && !existGameRoom(unique)) {
            addGameRoom(roomManager->at(unique));
        }
    }
}