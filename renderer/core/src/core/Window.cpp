
#include <core/Window.h>

#include "core/Window.h"

namespace blitz
{
    Window::Window(Context* context, bool isContextOwner)
    : context(context), isContextOwner(isContextOwner)
    {
    }

    const Context& Window::getContext() const { return *context; }

    Window::~Window()
    {
        if (isContextOwner)
        {
            delete context;
        }
    }
} // namespace blitz