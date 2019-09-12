#pragma once
#include <cstddef>
#include <functional>
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
    const auto hashString = std::hash<std::string>{};
}