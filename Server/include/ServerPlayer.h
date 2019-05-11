//
// Created by chaed on 19. 2. 22.
//

#ifndef SDL2_TETRIS_SERVER_SERVERPLAYER_H
#define SDL2_TETRIS_SERVER_SERVERPLAYER_H

#include <memory>

#include "Tetris/include/TFigureController.h"
#include "GameInterface/include/ManagerController.h"
#include "GameInterface/include/Player.h"

#include "PlayerService.h"

namespace server {

class ServerPlayer : public game_interface::Player
{

public:

    ServerPlayer();

    virtual ~ServerPlayer() = default;

    inline virtual const std::string_view& getUniqueName() const override final
    { return game_interface::NAME_PLAYER; }

    virtual void updateObserver(const game_interface::packet::Packet&) override final;

    virtual Json::Value toJson() const override final;

    virtual void fromJson(const Json::Value& json) override final;

    void enterRoom(const size_t order);

    void disconnection();

    void sendPacket(const game_interface::packet::Packet&) const override final;

    void sendUniqueInfo();

    void recvInitInfo(const game_interface::packet::Packet packet);

    std::shared_ptr<PlayerService> m_service = nullptr;

private:
    std::unique_ptr<tetris_module::TFigureController> m_ctl = nullptr;

};

}

#endif //SDL2_TETRIS_SERVER_SERVERPLAYER_H
