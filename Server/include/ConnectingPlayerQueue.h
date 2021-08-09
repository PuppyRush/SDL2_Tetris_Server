//
// Created by chaed on 19. 2. 26.
//

#ifndef SDL2_TETRIS_SERVER_CONNECTINGPLAYERQUEUE_H
#define SDL2_TETRIS_SERVER_CONNECTINGPLAYERQUEUE_H

#include <boost/serialization/singleton.hpp>

#include "GameInterface/include/ManagerInterface.h"
#include "GameInterface/include/VectorSubject.h"
#include "ServerPlayer.h"

namespace server {

class ConnectingPlayerQueue : public game_interface::VectorSubject<ServerPlayer>,
                              public game_interface::ManagerInterface,
                              public boost::serialization::singleton<ConnectingPlayerQueue>
{
public:

    using _Base = game_interface::VectorSubject<ServerPlayer>;
    using element_type = typename _Base::element_type;
    using unique_type = typename _Base::unique_type;

    friend class boost::serialization::singleton<ConnectingPlayerQueue>;

    ConnectingPlayerQueue()
    {}

    virtual ~ConnectingPlayerQueue()
    {}

    virtual void notify() override
    {}

    virtual void updateObserver(const game_interface::packet::Packet& packet);

    virtual void boradcast(game_interface::packet::Packet& packet) override;

    virtual void detach(ManagerInterface::unique_type) override;

    virtual ManagerInterface::unique_type findUser(ManagerInterface::unique_type);

    static std::shared_ptr<ConnectingPlayerQueue> getInstance();

protected:

    virtual void postAttach(const element_type&) override;

    virtual void postDetach(const unique_type unique) override;

private:

};

}

#endif //SDL2_TETRIS_SERVER_CONNECTINGPLAYERQUEUE_H
