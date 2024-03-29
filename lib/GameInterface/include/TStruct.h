//
// Created by chaed on 18. 12. 22.
//

#ifndef GAMEINTERFACE_TSTRUCT_H
#define GAMEINTERFACE_TSTRUCT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <cassert>
#include <string>
#include <functional>
#include <iostream>

#include "Type.h"

namespace game_interface {

typedef struct TIPString
{
    TIPString()
            : TIPString({192, 168, 0, 1}, 12345)
    {

    }

    TIPString(std::initializer_list<size_t> fields, const t_port port)
            : port(port)
    {
        assert(fields.size() == 4);
        ip.reserve(16);
        for (size_t b : fields) {
            ip.append(std::to_string(static_cast<long>(b)));
            ip.append(".");
        }
        ip.pop_back();
    }

    std::string operator*() const
    {
        return ip;
    }

    std::string getIpAndPortString() const
    {
        std::string ipAndport{ ip };
        ipAndport.append(":");
        ipAndport.append(std::to_string(port));
        return ipAndport;
    }

    std::string ip;
    t_port port;
} TIPString;


}

#endif //SDL2EASYGUI_TSTRUCT_H
