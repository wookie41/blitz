#include "core/Window.h"

namespace blitz
{
    Window::Window(Context* context, bool isContextOwner, Framebuffer* defaultFramebuffer)
    : context(context), isContextOwner(isContextOwner), framebuffer(defaultFramebuffer)
    {
    }

    Context& Window::getContext() const { return *context; }

    Window::~Window()
    {
        if (isContextOwner)
        {
            delete context;
        }
    }
} // namespace blitz