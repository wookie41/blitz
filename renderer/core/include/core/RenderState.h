#pragma once

#include "Color.h"

namespace blitz
{
    struct ViewPort
    {
        uint16_t x, y;
        uint16_t width, height;
    };

    enum class Projection
    {
        ORTHOGONAL,
        PERSPECTIVE
    };


    class Shader;

    struct RenderState
    {
        Color clearColor;
        ViewPort viewPort;
        Projection projection;
        bool enableDepthTest;
        bool enableStenciLTest;
        Shader* shader;
    };
} // namespace blitz