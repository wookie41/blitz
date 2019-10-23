#pragma once

#include "core/Window.h"

class SDL_Window;

namespace blitz
{
    class SDL2Context;

    class SDL2Window : public Window
    {
      public:
        explicit SDL2Window(SDL_Window* window, SDL2Context* context, bool isContextOwner);

        void swapBuffers() override;

        void show() const override;
        void hide() const override;

        ~SDL2Window();

      private:
        SDL_Window* window;
    };
} // namespace blitz