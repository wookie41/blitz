#pragma once

#include <functional>
#include <blitzcommon/DataType.h>

namespace blitz
{
    struct EnumClassHash
    {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    using hash = std::size_t;
    //const auto hashString = std::hash<std::string>{};

    uint32 hashString(char *str)
    {
        unsigned int h;
        unsigned char *p;

        h = 0;
        for (p = (unsigned char*)str; *p != '\0'; p++)
            h = 37 * h + *p;
        return h;
    }
}