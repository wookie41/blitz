#pragma once

#include "core/Device.h"

struct SDL_Window;

namespace blitz
{
    class SDL2Device : public Device
    {
      public:

        explicit SDL2Device();

        Window* createWindow(const WindowDef& windowDef) const override;

        Window* createWindow(const WindowDef &windowDef,
                             Context* contextToShare) const override;

        ~SDL2Device();
    private:

        SDL_Window* createSDLWindow(const WindowDef &windowDef) const;
    };
} // namespace blitz