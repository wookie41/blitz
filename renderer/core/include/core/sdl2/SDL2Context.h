#pragma once

#include "core/Context.h"

typedef void *SDL_GLContext;

namespace blitz
{

    class SDL2Context: public Context
    {
    public:
        explicit SDL2Context(SDL_GLContext context);

        const SDL_GLContext getSDLContext() const;

        ~SDL2Context();

    private:
        SDL_GLContext context;
    };
}