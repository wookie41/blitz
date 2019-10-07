#pragma once

#include <core/DataType.h>
namespace blitz
{
    enum class ColorType
    {
        RGB,
        RGBA
    };

    struct Color
    {
        uint8 red;
        uint8 green;
        uint8 blue;
        uint8 alpha;
    };
} // namespace blitz