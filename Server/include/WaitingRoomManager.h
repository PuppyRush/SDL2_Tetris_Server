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

#include "GameInterface/include/ManagerInterface.h"
#include "GameInterface/include/VectorSubject.h"
#include "GameInterface/include/Packet.h"

#include "ServerPlayer.h"
#include "ServerWaitingRoom.h"

namespace server {

class WaitingRoomManager : public game_interface::VectorSubject<ServerWaitingRoom>,
                           public game_interface::ManagerInterface,
                           public boost::serialization::singleton<WaitingRoomManager>
{
public:

    using _Base = game_interface::VectorSubject<ServerWaitingRoom>;
    using element_type = typename _Base::element_type;
    using unique_type = typename _Base::unique_type;

    friend class boost::serialization::singleton<WaitingRoomManager>;

    WaitingRoomManager()
    {}

    virtual ~WaitingRoomManager()
    {}

    virtual void notify() override
    {}

    virtual void updateObserver(const game_interface::packet::Packet& packet);

    virtual void boradcast(game_interface::packet::Packet& packet) override;

    void sendInitInfo(const game_interface::packet::Packet& packet);

    virtual void detach(ManagerInterface::unique_type) override;

    virtual ManagerInterface::unique_type findUser(ManagerInterface::unique_type);

    void exitUserFromWaitingRoom(_Base::unique_type unique);

    static std::shared_ptr<WaitingRoomManager> getInstance()
    {
        static auto inst = std::shared_ptr<WaitingRoomManager>
                (&boost::serialization::singleton<WaitingRoomManager>::get_mutable_instance());
        return inst;
    }

    void sendGameRoomsInfo();


protected:

    virtual void postAttach(const element_type&) override;

    virtual void postDetach(const unique_type unique) override;

private:
    void sendCreateWaitingRoom(element_type);
};

}
#endif //SDL2_TETRIS_SERVER_WAITINGROOMMANAGER_H
