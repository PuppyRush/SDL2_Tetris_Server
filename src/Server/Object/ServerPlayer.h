//
// Created by chaed on 19. 2. 22.
//

#ifndef SDL2_TETRIS_SERVER_SERVERPLAYER_H
#define SDL2_TETRIS_SERVER_SERVERPLAYER_H

#include <memory>
#include "GameInterface/SubScription/ManagerController.h"
#include "GameInterface/Object/Player.h"
#include "Server/PlayerService.h"

namespace server {

class ServerPlayer : public game_interface::Player
{

public:

    ServerPlayer() = default;

    virtual ~ServerPlayer() = default;

    virtual void updateObserver(const game_interface::Packet&) override;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json) override;

    inline virtual const std::string_view& getUniqueName() const
    { return game_interface::NAME_PLAYER; }

    void disconnection();

    void sendPacket(game_interface::Packet&);

    void sendUniqueInfo();

    void recvInitInfo(const game_interface::Packet packet);

    std::shared_ptr<PlayerService> m_service;
private:
};

}

#endif //SDL2_TETRIS_SERVER_SERVERPLAYER_H
