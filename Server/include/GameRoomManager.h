//
// Created by chaed on 19. 3. 20.
//

#ifndef SDL2_TETRIS_SERVER_GAMEROOMMANAGER_H
#define SDL2_TETRIS_SERVER_GAMEROOMMANAGER_H

//
// Created by chaed on 19. 2. 24.
//

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "ServerPlayer.h"
#include "ServerGameRoom.h"
#include "GameInterface/include/ManagerInterface.h"
#include "GameInterface/include/VectorSubject.h"
#include "GameInterface/include/Packet.h"

namespace server {

class GameRoomManager : public game_interface::VectorSubject<ServerGameRoom>,
                        public game_interface::ManagerInterface,
                        public boost::serialization::singleton<ServerGameRoom>
{
public:

    using _Base = game_interface::VectorSubject<ServerGameRoom>;
    using element_type = typename _Base::element_type;
    using unique_type = typename _Base::unique_type;

    friend class boost::serialization::singleton<GameRoomManager>;

    GameRoomManager()
    {}

    virtual ~GameRoomManager()
    {}

    virtual void notify() override
    {}

    virtual void updateObserver(const game_interface::packet::Packet& packet);

    virtual void boradcast(game_interface::packet::Packet& packet) override;

    virtual void detach(ManagerInterface::unique_type) override;

    virtual ManagerInterface::unique_type findUser(ManagerInterface::unique_type);

    static std::shared_ptr<GameRoomManager> getInstance()
    {
        static auto inst = std::shared_ptr<GameRoomManager>
                (&boost::serialization::singleton<GameRoomManager>::get_mutable_instance());
        return inst;
    }

protected:
    virtual void postAttach(const element_type&) override;

    virtual void postDetach(const unique_type unique) override;

private:
    void sendCreateWaitingRoom(element_type);
};

}

#endif //SDL2_TETRIS_SERVER_GAMEROOMMANAGER_H
