#pragma once

#include <core/ogl/OpenGLContext.h>

typedef void* SDL_GLContext;

namespace blitz
{
    class SDL2Context : public ogl::OpenGLContext
    {
      public:
        explicit SDL2Context(SDL_GLContext context);

        SDL_GLContext getSDLContext() const;

        ~SDL2Context();

      private:
        SDL_GLContext context;
    };
} // namespace blitz