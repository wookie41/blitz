#include <platform/input/SDLInputManager.h>

namespace blitz::platform
{
    const KeyboardState* SDLInputManager::getDefaultKeyboardState() const { this-> }
    const KeyboardState* SDLInputManager::getKeybaordState(uint8 keybordID) const;

    const MouseState* SDLInputManager::getDefaultMosueState() const;
    const MouseState* SDLInputManager::getMouseState(uint8 mouseID) const;

} // namespace blitz::platform