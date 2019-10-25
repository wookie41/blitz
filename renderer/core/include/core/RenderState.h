#pragma once

#include <core/Color.h>

namespace blitz
{
    struct ViewPort
    {
        uint16_t x, y;
        uint16_t width, height;
    };

    enum class Projection
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };


    class Shader;
    class Framebuffer;

    struct RenderState
    {
        Color clearColor;
        ViewPort viewPort;
        Projection projection;
        bool enableDepthTest;
        bool enableStencilTest;
        Shader* shader;
        Framebuffer* framebuffer;
        bool shouldSwapBuffers;
    };
} // namespace blitz