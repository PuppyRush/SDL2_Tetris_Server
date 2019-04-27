//
// Created by chaed on 19. 2. 26.
//

#ifndef SDL2_TETRIS_SERVER_CONNECTINGPLAYERQUEUE_H
#define SDL2_TETRIS_SERVER_CONNECTINGPLAYERQUEUE_H

#include <boost/serialization/singleton.hpp>

#include "GameInterface/SubScription/ManagerInterface.h"
#include "GameInterface/SubScription/VectorSubject.h"
#include "../Object/ServerPlayer.h"

namespace server {

class ConnectingPlayerQueue : public game_interface::VectorSubject<ServerPlayer>,
                              public game_interface::ManagerInterface,
                              public boost::serialization::singleton<ConnectingPlayerQueue>
{
public:

    using _Base = game_interface::VectorSubject<ServerPlayer>;

    friend class boost::serialization::singleton<ConnectingPlayerQueue>;

    ConnectingPlayerQueue()
    {}

    virtual ~ConnectingPlayerQueue()
    {}

    virtual void notify() override
    {}

    virtual void updateObserver(const game_interface::Packet& packet);

    virtual void boradcast(game_interface::Packet& packet) override;

    virtual void detach(ManagerInterface::unique_type) override;

    virtual ManagerInterface::unique_type findUser(ManagerInterface::unique_type) override;

    virtual Json::Value toJson() const override
    {}

    virtual const std::string_view& getUniqueName() const override
    {}

    static std::shared_ptr<ConnectingPlayerQueue> getInstance();

protected:

    virtual void postDetach(_Base::unique_type) override;

    virtual void postAttach(object_type) override;

private:

};

}

#endif //SDL2_TETRIS_SERVER_CONNECTINGPLAYERQUEUE_H
