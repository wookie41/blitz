#pragma once

#include <blitzcommon/NonCopyable.h>
#include <core/RenderCommand.h>
#include <core/RenderState.h>

namespace blitz
{

    struct ViewPort;
    class Window;
    class RenderPass;

    class Renderer: NonCopyable
    {
    public:
        virtual void issue(RenderPass* renderPass) = 0;
        virtual void render(Window* window) = 0;

    protected:
        virtual void run(RenderCommand *renderCommand) = 0;
        virtual void setViewPort(const ViewPort* viewPort) = 0;
    };
}