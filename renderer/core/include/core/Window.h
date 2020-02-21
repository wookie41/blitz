#pragma once

#include <core/Color.h>
#include <core/Context.h>
#include <core/Precompiled.h>

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

        Framebuffer* getFramebuffer() const;

        virtual void prepare() = 0;

        virtual void swapBuffers() = 0;

        virtual void setClearColor(const Color& color) = 0;
        virtual void setClearDepth(const float& color) = 0;
        virtual void setClearStencil(const int& color) = 0;

        virtual void clearColor() = 0;
        virtual void clearDepth() = 0;
        virtual void clearStencil() = 0;

        virtual void show() const = 0;
        virtual void hide() const = 0;

        virtual ~Window();

      protected:
        Color clearColorColor;
        Color clearDepthColor;
        Color clearStencilColor;

      private:
        Context* context;
        bool isContextOwner;
        Framebuffer* framebuffer;
    };
} // namespace blitz