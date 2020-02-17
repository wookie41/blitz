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
        virtual const KeyboardState* getKeyboardState() const = 0;
        virtual const MouseState* getMouseState() const = 0;

        virtual ~InputManager() = default;
    };
} // namespace blitz::platform