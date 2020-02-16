#pragma once

#include <platform/input/InputManager.h>

namespace blitz::platform
{
    constexpr const uint8 MAX_MICES = 2;
    constexpr const uint8 MAX_KEYBOARDS = 2;

    class SDLInputManager : public InputManager
    {
      public:
        void readInput() override;

        const KeyboardState* getDefaultKeyboardState() const override;
        const KeyboardState* getKeybaordState(uint8 keybordID) const override;

        const MouseState* getDefaultMosueState() const override;
        const MouseState* getMouseState(uint8 mouseID) const override;

      private:

        inline void updateInputDevices();

        MouseState micesStates[MAX_MICES] = { nullptr };
        KeyboardState keyboardsStates[MAX_KEYBOARDS] = { nullptr };
    }
} // namespace blitz::platform