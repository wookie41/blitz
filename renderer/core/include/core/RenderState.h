#pragma once

#include <core/Color.h>
#include <core/Precompiled.h>

namespace blitz
{
    struct ViewPort
    {
        int32_t x, y;
        int32_t width, height;
        float near, far;
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