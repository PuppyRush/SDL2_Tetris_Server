
#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <string_view>
#include <memory>

#include <jsoncpp/json/json.h>

#include "Atomic.h"
#include "../include/Constant.h"
#include "../include/Type.h"

namespace game_interface {

class Object
{
public:

    using unique_type = t_unique;

    virtual ~Object()
    {}

    inline const bool compareUnique(const unique_type unique) const noexcept
    { return m_unique == unique; }

    inline void setUnique(const unique_type unique) noexcept
    { m_unique = unique; }

    inline const unique_type getUnique() const noexcept
    { return m_unique; }

    inline const t_time getMaketime() const noexcept
    { return m_maketime; }

    inline void setMaketime(const t_time time) noexcept
    { m_maketime = time; }

    virtual Json::Value toJson() const;

    virtual void fromJson(const Json::Value& json);

    virtual const std::string_view& getUniqueName() const = 0;

protected:
    Object();

private:
    unique_type m_unique;
    t_time m_maketime;
};

}

#endif