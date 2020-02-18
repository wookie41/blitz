#pragma once

#include <core/Precompiled.h>
#include <core/RenderCommand.h>
#include <core/RenderState.h>

namespace blitz
{

    class Window;
    struct ViewPort;
    class RenderPass;

    class Renderer: NonCopyable
    {
    public:
        virtual void issue(RenderPass* renderPass) = 0;
        virtual void render() = 0;

    protected:
        virtual void run(RenderCommand *renderCommand) = 0;
        virtual void setViewPort(const ViewPort* viewPort) = 0;
    };
}