#pragma once

#include <core/Precompiled.h>
#include <core/Context.h>
#include <core/Color.h>

namespace blitz
{
    class RenderPass;
    class Framebuffer;

    struct WindowDef
    {
        uint32 x, y;
        uint32 width, height;
        const char* const title;
    };

    class Window : private NonCopyable
    {
      public:
        explicit Window(Context* context, bool isContextOwner, Framebuffer* defaultFramebuffer);
        Context& getContext() const;

        Framebuffer *getFramebuffer() const;

        virtual void prepare() = 0;
        virtual void clearColor(const Color& color) = 0;
        virtual void clearDepth(const Color& color) = 0;
        virtual void clearStencil(const Color& color) = 0;

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