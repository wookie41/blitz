#pragma once

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

    using hash = size_t;
    hash hashString(const char* str, const size_t strLen = -1);
} // namespace blitz