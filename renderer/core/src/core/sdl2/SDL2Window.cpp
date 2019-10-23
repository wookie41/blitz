#include <SDL2/SDL.h>
#include <core/sdl2/SDL2Window.h>
#include <core/sdl2/SDL2Context.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>

static blitz::ogl::OpenGLFramebuffer defaultFramebuffer { 0 }; // NOLINT(cert-err58-cpp)

namespace blitz
{
    SDL2Window::SDL2Window(SDL_Window* window, SDL2Context* context, bool isContextOwner)
    : Window(context, isContextOwner, &defaultFramebuffer), window(window) {}

    SDL2Window::~SDL2Window() { SDL_DestroyWindow(window); }

    void SDL2Window::swapBuffers()
    {
        //TODO
    }

    void SDL2Window::show() const
    {
        SDL_ShowWindow(window);
    }

    void SDL2Window::hide() const
    {
        SDL_HideWindow(window);
    }
} // namespace blitz