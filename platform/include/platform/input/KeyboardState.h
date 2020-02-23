#pragma once
#include <platform/Precompiled.h>

namespace blitz::platform
{
    const constexpr uint64 KEY_W = 0;
    const constexpr uint64 KEY_S = 1;
    const constexpr uint64 KEY_A = 2;
    const constexpr uint64 KEY_D = 3;
    const constexpr uint64 KEY_ESCAPE = 4;
    const constexpr uint64 KEY_SPACE = 5;
    const constexpr uint64 KEY_LEFT_CTRL = 6;

    struct KeyboardState
    {
        // each bit in the array represents one key
        // if the bit is set, the key is down, if not, the key is up
        uint64 keysState[2] = { 0, 0 };
    };

    inline void setDown(KeyboardState* keyboardState, const uint64& keyCode)
    {
        keyboardState->keysState[keyCode / 64] |= (1 << (keyCode % 64));
    }

    inline void setUp(KeyboardState* keyboardState, const uint64& keyCode)
    {
        keyboardState->keysState[keyCode / 64] &= (~(1 << (keyCode % 64)));
    }

    inline bool isDown(const KeyboardState* keyboardState, const uint64& keyCode)
    {
        return keyboardState->keysState[keyCode / 64] & (1 << (keyCode % 64));
    }

    inline bool isUp(const KeyboardState* keyboardState, const uint64& keyCode)
    {
        return !isDown(keyboardState, (keyCode % 64));
    }
} // namespace blitz::platform
