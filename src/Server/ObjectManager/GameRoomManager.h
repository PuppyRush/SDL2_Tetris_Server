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

#include "Server/Object/ServerPlayer.h"
#include "Server/Object/ServerGameRoom.h"
#include "GameInterface/SubScription/ManagerInterface.h"
#include "GameInterface/SubScription/VectorSubject.h"
#include "GameInterface/Online/Packet.h"

namespace server {

class GameRoomManager : public game_interface::VectorSubject<ServerGameRoom>,
                        public game_interface::ManagerInterface,
                        public boost::serialization::singleton<ServerGameRoom>
{
public:

    using _Base = game_interface::VectorSubject<ServerGameRoom>;

    friend class boost::serialization::singleton<GameRoomManager>;

    GameRoomManager()
    {}

    virtual ~GameRoomManager()
    {}

    virtual void notify() override
    {}

    virtual void updateObserver(const game_interface::Packet& packet);

    virtual void boradcast(game_interface::Packet& packet) override;

    virtual void detach(ManagerInterface::unique_type) override;

    virtual ManagerInterface::unique_type findUser(ManagerInterface::unique_type) override;

    virtual const std::string_view& getUniqueName() const override
    {}

    virtual Json::Value toJson() const override
    {};

    static std::shared_ptr<GameRoomManager> getInstance()
    {
        static auto inst = std::shared_ptr<GameRoomManager>
                (&boost::serialization::singleton<GameRoomManager>::get_mutable_instance());
        return inst;
    }

protected:
    virtual void postDetach(_Base::unique_type) override;

    virtual void postAttach(object_type) override;

private:
    void sendCreateWaitingRoom(object_type);
};

}

#endif //SDL2_TETRIS_SERVER_GAMEROOMMANAGER_H
