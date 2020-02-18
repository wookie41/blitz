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
    struct UniformState;
	
    struct RenderState
    {
        ViewPort viewPort;
        bool enableDepthTest;
        bool enableStencilTest;
        Shader* shader;
        Framebuffer* framebuffer;
        std::vector<UniformState*> renderPassWideUniforms;
    };
} // namespace blitz