#pragma once

#include <platform/Precompiled.h>

namespace blitz::platform
{
    constexpr const uint32 LEFT_MOUSE_BUTTON = 1 << 0;
    constexpr const uint32 RIGHT_MOUSE_BUTTON = 1 << 1;

    struct MouseState
    {
        uint32 pressedButtons;
        Vector2i absolutePos;
        Vector2i relativePos;
        uint32 wheelProgress;
    };

    inline void setDown(MouseState* mouseState, const uint32& button) { mouseState->pressedButtons |= (1 << button); }

    inline void setUp(MouseState* mouseState, const uint32& button) { mouseState->pressedButtons &= (~(1 << button)); }

    inline bool isDown(const MouseState* mouseState, const uint32& button)
    {
        return mouseState->pressedButtons & (1 << button);
    }

    inline bool isUp(const MouseState* mouseState, const uint32& button) { return !isDown(mouseState, button); }

} // namespace blitz::platform
