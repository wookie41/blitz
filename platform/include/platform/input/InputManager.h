#pragma once

#include <blitzcommon/DataType.h>
#include <blitzcommon/NonCopyable.h>

namespace blitz::platform
{
    struct KeyboardState;
    struct MouseState;

    enum class InputDeviceType
    {
        KEYBOARD,
        MOUSE
    };

    class InputManager : public NonCopyable
    {
      public:
        virtual void readInput() = 0;

        virtual const KeyboardState* getDefaultKeyboardState() const = 0;
        virtual const KeyboardState* getKeybaordState(uint8 keybordID) const = 0;

        virtual const MouseState* getDefaultMosueState() const = 0;
        virtual const MouseState* getMouseState(uint8 mouseID) const = 0;

        virtual ~InputManager() = default;
    };
} // namespace blitz::platform