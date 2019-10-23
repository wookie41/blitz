#pragma once

#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    // RenderPass encapsulates the process of drawing a single frame
    // The frame doesn't have to be drawn to a window (the default frame buffer),
    // it can be drawn to a texture and used for later processing

    class RenderState;
    class RenderCommand;

    class RenderPass : NonCopyable
    {
      public:
        explicit RenderPass(RenderState* renderState);

        virtual void add(RenderCommand* renderCommand) = 0;

        virtual const RenderState& getRenderState() = 0;


        //this method should be called before the first call to getNextCommand
        //so RenderPass can optimize the order of commands to be issued
        virtual void finish() = 0;

        // Returns a pointer to the next RenderCommand that should be issued
        // if no more commands are available, a nullptr is returned.
        // This allows the RenderPass to optimize the order of the commands
        // that should be issued.
        // For example, the RenderPass can sort commands by the shader used, to minimize the amount of
        // switches between different shaders.

        virtual RenderCommand* getNextCommand() = 0;

        virtual ~RenderPass();

      private:
        RenderState* renderState;
    };
} // namespace blitz