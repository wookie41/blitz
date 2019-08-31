#pragma once

#include "Context.h"
#include "blitzcommon/Utils.h"
#include <cstdint>

class RenderPass;

namespace blitz
{
    struct WindowDef
    {
        uint32_t x, y;
        uint32_t width, height;
        const char* title;
    };

    class Window : private NonCopyable
    {
      public:
        explicit Window(Context* context, bool isContextOwner);
        const Context& getContext() const;

        // issue just adds the RenderPass to the window's queue
        // it doesn't result in any draw calls
        virtual void issue(RenderPass* renderPass) = 0;

        // render should process all of the RenderPasses that have been issued
        // since the last render was called. The render doesn't result in
        // swapping the buffers, ie. showing a frame.
        virtual void render() = 0;

        virtual void swapBuffers() = 0;

        virtual void show() const = 0;
        virtual void hide() const = 0;

        virtual ~Window();

      private:
        Context* context;
        bool isContextOwner;
    };
} // namespace blitz