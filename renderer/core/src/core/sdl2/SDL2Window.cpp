#include <SDL2/SDL.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>
#include <core/sdl2/SDL2Context.h>
#include <core/sdl2/SDL2Window.h>

static blitz::ogl::OpenGLFramebuffer defaultFramebuffer{ 0 }; // NOLINT(cert-err58-cpp)

namespace blitz
{
    SDL2Window::SDL2Window(SDL_Window* window, SDL2Context* context, SDL_GLContext glContext, bool isContextOwner)
    : Window(context, isContextOwner, &defaultFramebuffer), window(window), glContext(glContext)
    {
    }

    SDL2Window::~SDL2Window() { SDL_DestroyWindow(window); }

    void SDL2Window::swapBuffers() { SDL_GL_SwapWindow(window); }

    void SDL2Window::show() const { SDL_ShowWindow(window); }

    void SDL2Window::hide() const { SDL_HideWindow(window); }

    void SDL2Window::clearDepth(const Color& color)
    {
        glClearColor(color.red, color.green, color.blue, color.alpha);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void SDL2Window::clearStencil(const Color& color)
    {
        glClearColor(color.red, color.green, color.blue, color.alpha);
        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void SDL2Window::clearColor(const Color& color)
    {
        glClearColor(color.red, color.green, color.blue, color.alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SDL2Window::prepare()
    {
        SDL_GL_MakeCurrent(window, glContext);
    }
} // namespace blitz