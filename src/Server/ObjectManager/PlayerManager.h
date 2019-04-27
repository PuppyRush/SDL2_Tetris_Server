//
// Created by chaed on 19. 2. 24.
//

#ifndef SDL2_TETRIS_SERVER_PLAYERMANAGER_H
#define SDL2_TETRIS_SERVER_PLAYERMANAGER_H

#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>

#include "GameInterface/SubScription/ManagerInterface.h"
#include "GameInterface/SubScription/MapSubject.h"
#include "../Object/ServerPlayer.h"

namespace server {

class PlayerManager : public game_interface::MapSubject<ServerPlayer>,
                      public game_interface::ManagerInterface,
                      public boost::serialization::singleton<PlayerManager>
{
public:

    using _Base = game_interface::MapSubject<ServerPlayer>;

    friend class boost::serialization::singleton<PlayerManager>;

    PlayerManager()
    {}

    virtual ~PlayerManager()
    {}

    virtual void notify() override
    {}

    virtual void updateObserver(const game_interface::Packet& packet);

    virtual void boradcast(game_interface::Packet& packet) override;

    virtual void detach(ManagerInterface::unique_type) override;

    virtual ManagerInterface::unique_type findUser(ManagerInterface::unique_type) override;

    virtual Json::Value toJson() const override
    {};

    virtual const std::string_view& getUniqueName() const override
    {}

    static std::shared_ptr<PlayerManager> getInstance()
    {

        static auto inst = std::shared_ptr<PlayerManager>
                (&boost::serialization::singleton<PlayerManager>::get_mutable_instance());
        return inst;
    }

protected:

    virtual void postDetach(_Base::unique_type) override;

    virtual void postAttach(object_type) override;

private:

};

}
#endif //SDL2_TETRIS_SERVER_PLAYERMANAGER_H
