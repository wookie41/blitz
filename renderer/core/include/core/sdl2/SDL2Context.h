#pragma once

#include "core/ogl/OpenGLContext.h"

typedef void* SDL_GLContext;

namespace blitz
{

    class SDL2Context : public OpenGLContext
    {
      public:
        explicit SDL2Context(SDL_GLContext context);

        ~SDL2Context();

    private:
        SDL_GLContext context;

    };
} // namespace blitz