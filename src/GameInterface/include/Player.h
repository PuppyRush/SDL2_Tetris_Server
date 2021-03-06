//
// Created by chaed on 19. 1. 13.
//

#ifndef OBJECT_PLAYER_H
#define OBJECT_PLAYER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "GameInterface/src/SubScription/Observer.h"

namespace game_interface {

class Player : public Observer
{
public:

    Player() = default;

    virtual ~Player() = default;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json);

    inline const std::string getUserName() const noexcept
    { return m_name; }

    inline void setUserName(const std::string& name)
    { m_name = name; }

    inline bool isMaster() const
    { return m_isMaster; }

    inline void setMaster(bool b)
    { m_isMaster = b; }

    virtual void updateObserver(const Packet&) = 0;

    virtual void sendPacket(game_interface::Packet&) = 0;

private:
    std::string m_name;
    bool m_isMaster = false;
public:
};

}

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H
