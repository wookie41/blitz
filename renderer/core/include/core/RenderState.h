#pragma once

#include <core/Color.h>
#include <core/Precompiled.h>

namespace blitz
{
    struct ViewPort
    {
        uint16_t x, y;
        uint16_t width, height;
        uint16_t near, far;
    };

    enum class Projection
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    class Shader;
    class Framebuffer;
    struct UniformState;
	
    struct RenderState
    {
        ViewPort viewPort;
        Projection projection;
        bool enableDepthTest;
        bool enableStencilTest;
        Shader* shader;
        Framebuffer* framebuffer;
        std::vector<UniformState*> renderPassWideUniforms;
    };
} // namespace blitz