#pragma once

#include <core/Window.h>

struct SDL_Window;
typedef void *SDL_GLContext;

namespace blitz
{
    class SDL2Context;

    class SDL2Window : public Window
    {
      public:
        explicit SDL2Window(SDL_Window* window, SDL2Context* context, SDL_GLContext glContext, bool isContextOwner);

        void prepare() override;

        void setClearColor(const Color& color) override;
        void setClearDepth(const float& color) override;
        void setClearStencil(const int& color) override;

        void clearColor() override;
        void clearDepth() override;
        void clearStencil() override;

        void swapBuffers() override;

        void show() const override;
        void hide() const override;

        ~SDL2Window();

      private:
        SDL_Window* window;
        SDL_GLContext glContext;
    };
} // namespace blitz