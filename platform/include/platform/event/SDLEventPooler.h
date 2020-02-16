#pragma once

#include <platform/event/EventPooler.h>

namespace blitz::platform
{
    class SDLInputManager;

    class SDLEventPooler : public EventPooler
    {
      public:
        explicit SDLEventPooler(SDLInputManager* inputHandler);

        void poolEvents() override;

      private:
        SDLInputManager* sdlInputManager;
    };
} // namespace blitz::platform
