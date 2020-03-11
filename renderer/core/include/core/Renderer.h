#pragma once

#include <core/Precompiled.h>
#include <core/RenderCommand.h>
#include <core/RenderState.h>
#include <core/RenderPass.h>

namespace blitz
{

    class Window;
    struct ViewPort;

    class Renderer: NonCopyable
    {
    public:
        virtual void issue(RenderPass* renderPass) = 0;
        virtual void render() = 0;

    protected:
        virtual void run(RenderCommand *renderCommand) = 0;
        virtual void setViewPort(const ViewPort* viewPort) = 0;
        virtual void setStencilTest(const bool& enabled) = 0;
        virtual void setDepthTest(const bool& enabled) = 0;
    };
}