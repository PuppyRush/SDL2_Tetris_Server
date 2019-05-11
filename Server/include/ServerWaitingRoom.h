//
// Created by chaed on 19. 2. 22.
//

#ifndef SDL2_TETRIS_SERVER_WAITINGROOM_H
#define SDL2_TETRIS_SERVER_WAITINGROOM_H

#include "GameInterface/include/WaitingRoom.h"

namespace server {

class ServerWaitingRoom : public game_interface::WaitingRoom
{

public:

    ServerWaitingRoom()
    {}

    virtual ~ServerWaitingRoom()
    {}

    virtual void updateObserver(const game_interface::packet::Packet&) override;

    inline virtual const std::string_view& getUniqueName() const
    { return game_interface::NAME_WAITINGROOM; }

    virtual void enter(const player_ptr& ply) override;

    virtual void exit(const unique_type) override;

    virtual void postEnter(const player_ptr& ply) override;

    virtual void postExit(const player_ptr&) override;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json) override;

    virtual void addGameRoom(const Room::room_ptr& room) override;

    virtual void removeGameRoom(const Room::unique_type unique) override;

    virtual void postAddedGameRoom(const room_ptr& room) override;

    virtual void postRemovedGameRoom(const unique_type unique) override;

    void broadcastChat(const game_interface::packet::Packet& packet);

    void recvRequestEnter(const game_interface::packet::Packet& packet);

    void recvRequestCreate(const game_interface::packet::Packet& packet);
};

}

#endif //SDL2_TETRIS_SERVER_WAITINGROOM_H
