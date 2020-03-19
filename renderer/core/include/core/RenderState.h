#pragma once

#include <core/Color.h>
#include <core/Precompiled.h>
#include <core/RenderCommand.h>

namespace blitz
{
    struct ViewPort
    {
        uint16 x, y;
        uint16 width, height;
        float near, far;
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
        const ViewPort* viewPort;
        Projection projection;
        bool enableDepthTest;
        bool enableStencilTest;
        bool enableBlendTest;
        //TODO alpha test function
        Shader* shader;
        Framebuffer* framebuffer;
        Array<UniformState>* renderPassWideUniforms;
    };
} // namespace blitz