//
// Created by chaed on 19. 2. 22.
//

#ifndef SDL2_TETRIS_SERVER_WAITINGROOM_H
#define SDL2_TETRIS_SERVER_WAITINGROOM_H

#include "GameInterface/Object/WaitingRoom.h"

namespace server {

class ServerWaitingRoom : public game_interface::WaitingRoom
{

public:

    ServerWaitingRoom()
    {}

    virtual ~ServerWaitingRoom()
    {}

    virtual void updateObserver(const game_interface::Packet&) override;

    inline virtual const std::string_view& getUniqueName() const
    { return game_interface::NAME_WAITINGROOM; }

    virtual void enter(player_ptr ply) override;

    virtual void exit(const unique_type) override;

    virtual void postEnter(player_ptr ply) override;

    virtual void postExit(const unique_type unique) override;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json) override;

    virtual void addGameRoom(Room::room_ptr room) override;

    virtual void removeGameRoom(const Room::unique_type unique) override;

    virtual void postAddedGameRoom(room_ptr room) override;

    virtual void postRemovedGameRoom(const unique_type unique) override;

    void broadcastChat(const game_interface::Packet& packet);

    void broadcast(game_interface::Packet& packet);

    void recvRequestEnter(const game_interface::Packet& packet);

    void recvRequestCreate(const game_interface::Packet& packet);
};

}

#endif //SDL2_TETRIS_SERVER_WAITINGROOM_H
