#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    struct Transform2D
    {
        Vector2f translate;
        Vector2f scale2;
        float rotation;
    };
} // namespace blitz