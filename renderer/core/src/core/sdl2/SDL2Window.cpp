#include "SDL2/SDL.h"
#include "core/sdl2/SDL2Window.h"
#include "core/sdl2/SDL2Context.h"

namespace blitz
{
    SDL2Window::SDL2Window(SDL_Window* window, SDL2Context* context, bool isContextOwner)
    : Window(context, isContextOwner), window(window) {}

    void SDL2Window::issue(RenderPass* renderPass)
    {
        // noop
    }

    void SDL2Window::render()
    {
        // noop
    }

    SDL2Window::~SDL2Window() { SDL_DestroyWindow(window); }

    void SDL2Window::swapBuffers()
    {

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