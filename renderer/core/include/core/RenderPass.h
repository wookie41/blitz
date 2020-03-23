#pragma once

#include <core/Precompiled.h>
#include <core/RenderCommand.h>

namespace blitz
{
    // RenderPass encapsulates the process of drawing a single frame
    // The frame doesn't have to be drawn to a window (the default frame buffer),
    // it can be drawn to a texture and used for later processing

    struct RenderState;

    class RenderPass : NonCopyable
    {
      public:
        RenderPass(const RenderState* state, const Array<RenderCommand>* commands);

        // this should be called if the commands should be reorder
        virtual void prepare() = 0;

        // Returns a pointer to the next RenderCommand that should be issued
        // if no more commands are available, a nullptr is returned.
        // This allows the RenderPass to optimize the order of the commands
        // that should be issued.
        // For example, the RenderPass can sort commands by the shader used, to minimize the amount of
        // switches between different shaders.

        const RenderState* getRenderState() const;

        virtual RenderCommand* getNextCommand() = 0;

        virtual ~RenderPass();

      protected:
        const Array<RenderCommand>* renderCommands;
        const RenderState* renderState;
    };
} // namespace blitz