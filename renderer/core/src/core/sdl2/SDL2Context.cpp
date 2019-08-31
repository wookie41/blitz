
#include "core/sdl2/SDL2Context.h"
#include "SDL2/SDL.h"

namespace blitz
{

    SDL2Context::SDL2Context(SDL_GLContext context) : context(context) {}

    const SDL_GLContext SDL2Context::getSDLContext() const { return context; }

    SDL2Context::~SDL2Context()
    {
        SDL_GL_DeleteContext(context);
    }

} // namespace blitz