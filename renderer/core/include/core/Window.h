#pragma once

#include <core/DataType.h>
#include <core/Context.h>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class RenderPass;
    class Framebuffer;

    struct WindowDef
    {
        uint32 x, y;
        uint32 width, height;
        const char* title;
    };

    class Window : private NonCopyable
    {
      public:
        explicit Window(Context* context, bool isContextOwner, Framebuffer* defaultFramebuffer);
        Context& getContext() const;

        virtual void swapBuffers() = 0;

        virtual void show() const = 0;
        virtual void hide() const = 0;

        virtual ~Window();

      private:
        Context* context;
        bool isContextOwner;
        Framebuffer* framebuffer;
    };
} // namespace blitz