#pragma once

#include "RenderCommand.h"
#include "RenderState.h"

namespace blitz
{
    // RenderPass encapsulates the process of drawing a single frame
    // The frame doesn't have to be drawn to a window (the default frame buffer),
    // it can be drawn to a texture and used for later processing

    class RenderPass
    {
    public:
        virtual void set(RenderState* renderState) = 0;

        virtual void add(RenderCommand* renderCommand)  = 0;

        const RenderState& getRenderState()  = 0;

        // Returns a pointer to the next RenderCommand that should be issued
        // if no more commands are available, a nullptr is returned.
        // This allows the RenderPass to optimize the order of the commands
        // that should be issued.
        // For example, the RenderPass by shaders, to minimize the amount of
        // switches between different shaders.

        RenderCommand* getNextCommand()  = 0;

        virtual ~RenderPass() = default;
    };
} // namespace blitz