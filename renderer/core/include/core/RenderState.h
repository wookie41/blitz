#pragma once

#include "Color.h"

namespace blitz
{
    struct ViewPort
    {
        uint16_t x, y;
        uint16_t width, height;
    };

    struct RenderState
    {
        Color clearColor;
        ViewPort viewPort;
    };
} // namespace blitz