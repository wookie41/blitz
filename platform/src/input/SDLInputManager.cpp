#include <platform/input/SDLInputManager.h>

namespace blitz::platform
{
    const KeyboardState* SDLInputManager::getDefaultKeyboardState() const { return nullptr; }
    const KeyboardState* SDLInputManager::getKeybaordState(uint8 keybordID) const { return nullptr; }

    const MouseState* SDLInputManager::getDefaultMosueState() const { return nullptr; }
    const MouseState* SDLInputManager::getMouseState(uint8 mouseID) const { return nullptr; }

} // namespace blitz::platform