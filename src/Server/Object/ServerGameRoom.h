//
// Created by chaed on 19. 3. 6.
//

#ifndef SDL2_TETRIS_SERVER_SERVERGAMEROOM_H
#define SDL2_TETRIS_SERVER_SERVERGAMEROOM_H

#include "GameInterface/Object/GameRoom.h"
#include "GameInterface/Online/Packet.h"
#include "GameInterface/Online/PacketQueue.h"

namespace server {

class ServerGameRoom : public game_interface::GameRoom
{
public:

    virtual void updateObserver(const game_interface::Packet&) override;

    void responseGameBoardInfo(const game_interface::Packet&);

    inline virtual const std::string_view& getUniqueName() const
    { return game_interface::NAME_GAMEROOM; }

    virtual void postEnter(player_ptr ply) override;

    virtual void postExit(const unique_type unique) override;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json) override;
};

}
#endif //SDL2_TETRIS_SERVER_SERVERGAMEROOM_H
