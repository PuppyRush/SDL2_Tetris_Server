//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_WAITINGROOMMANAGER_H
#define SDL2_TETRIS_SERVER_WAITINGROOMMANAGER_H

//
// Created by chaed on 19. 2. 24.
//

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "Server/Object/ServerPlayer.h"
#include "Server/Object/ServerWaitingRoom.h"
#include "GameInterface/SubScription/ManagerInterface.h"
#include "GameInterface/SubScription/VectorSubject.h"
#include "GameInterface/Online/Packet.h"

namespace server {

class WaitingRoomManager : public game_interface::VectorSubject<ServerWaitingRoom>,
                           public game_interface::ManagerInterface,
                           public boost::serialization::singleton<WaitingRoomManager>
{
public:

    using _Base = game_interface::VectorSubject<ServerWaitingRoom>;

    friend class boost::serialization::singleton<WaitingRoomManager>;

    WaitingRoomManager()
    {}

    virtual ~WaitingRoomManager()
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

    void exitUserFromWaitingRoom(_Base::unique_type unique);

    static std::shared_ptr<WaitingRoomManager> getInstance()
    {
        static auto inst = std::shared_ptr<WaitingRoomManager>
                (&boost::serialization::singleton<WaitingRoomManager>::get_mutable_instance());
        return inst;
    }

    void sendGameRoomsInfo();

    void sendInitInfo(const game_interface::Packet& packet);

protected:
    virtual void postDetach(_Base::unique_type) override;

    virtual void postAttach(object_type) override;

private:
    void sendCreateWaitingRoom(object_type);
};

}
#endif //SDL2_TETRIS_SERVER_WAITINGROOMMANAGER_H
