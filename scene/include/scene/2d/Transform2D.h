#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    struct Transform2D
    {
        Vector2f translate{ 0.f, 0.f };
        Vector2f scale{ 1.f, 1.f };
        float rotation = 0.f; // degress
    };
} // namespace blitz