//
// Created by chaed on 19. 3. 6.
//

#ifndef SDL2_TETRIS_SERVER_SERVERGAMEROOM_H
#define SDL2_TETRIS_SERVER_SERVERGAMEROOM_H

#include "GameInterface/include/GameRoom.h"
#include "GameInterface/include/Packet.h"
#include "GameInterface/include/PacketQueue.h"

namespace server {

class ServerGameRoom : public game_interface::GameRoom
{
public:

    virtual void updateObserver(const game_interface::packet::Packet&) override;

    void responseGameBoardInfo(const game_interface::packet::Packet&);

    inline virtual const std::string_view& getUniqueName() const
    { return game_interface::NAME_GAMEROOM; }

    virtual void enter(const player_ptr& ply) override
    {}

    virtual void exit(const unique_type unique) override
    {}

    virtual void postEnter(const player_ptr& ply) override;

    virtual void postExit(const player_ptr& ply) override;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json) override;

};

}
#endif //SDL2_TETRIS_SERVER_SERVERGAMEROOM_H
