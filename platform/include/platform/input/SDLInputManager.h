#pragma once

#include <platform/Precompiled.h>
#include <platform/input/InputManager.h>

namespace blitz::platform
{
    constexpr const uint8 MAX_MICES = 2;
    constexpr const uint8 MAX_KEYBOARDS = 2;

    class SDLEventPooler;

    class SDLInputManager : public InputManager
    {
      public:
        SDLInputManager();

        const KeyboardState* getKeyboardState() const override;
        const MouseState* getMouseState() const override;

        ~SDLInputManager();

      private:
        friend class SDLEventPooler;

        void handleKeyDownEvent(const SDL_KeyboardEvent* keyboardEvent);
        void handleKeyUpEvent(const SDL_KeyboardEvent* keyboardEvent);

        void handleMouseMovementEvent(const SDL_MouseMotionEvent* mouseMovementEvent);

        void handleMouseButtonDownEvent(const SDL_MouseButtonEvent* mouseButtonEvent);
        void handleMouseButtonUpEvent(const SDL_MouseButtonEvent* mouseButtonEvent);

        void handleMouseWheelEvent(const SDL_MouseWheelEvent* mouseWheelEvents);

        inline void updateInputDevices();

        MouseState* mouseState = nullptr;
        KeyboardState* keyboardState = nullptr;
    };
} // namespace blitz::platform