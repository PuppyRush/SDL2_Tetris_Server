//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_SUBJECT_H
#define TETRIS_FIGURE_CLASS_SUBJECT_H

#include "GameInterface/include/Type.h"
#include "GameInterface/Online/Packet.h"
#include "GameInterface/Object/Object.h"

namespace game_interface {

//pre-declarcation
class Observer : public Object
{
public:

    using unique_type = Object::unique_type;

    Observer() = default;

    virtual ~Observer()
    {}

    virtual void updateObserver(const Packet&) = 0;
};

}

#endif //TETRIS_FIGURE_CLASS_SUBJECT_H
