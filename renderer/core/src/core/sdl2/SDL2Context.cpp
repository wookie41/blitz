
#include <SDL2/SDL.h>
#include <core/sdl2/SDL2Context.h>
#include <core/RendererErrorCode.h>

namespace blitz
{
    SDL2Context::SDL2Context(SDL_GLContext context) : context(context) {}

    SDL2Context::~SDL2Context() { SDL_GL_DeleteContext(context); }

    SDL_GLContext SDL2Context::getSDLContext() const
    {
        return context;
    }
} // namespace blitz