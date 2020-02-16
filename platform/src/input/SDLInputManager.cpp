#include <platform/input/SDLInputManager.h>

namespace blitz::platform
{


    const KeyboardState* SDLInputManager::getKeyboardState() const { return keyboardState; }
    const MouseState* SDLInputManager::getMouseState() const { return mouseState; }

    void handleKeyDownEvent(const SDL_KeyboardEvent* keyboardEvent) {}
    void handleKeyUpEvent(const SDL_KeyboardEvent* keyboardEvent) {}

    void SDLInputManager::handleMouseMovementEvent(const SDL_MouseMotionEvent* mouseMovementEvent) {}

    void SDLInputManager::handleMouseButtonDownEvent(const SDL_MouseButtonEvent* mouseButtonEvent) {}
    void SDLInputManager::handleMouseButtonUpEvent(const SDL_MouseButtonEvent* mouseButtonEvent) {}

    void SDLInputManager::handleMouseWheelEvent(const SDL_MouseWheelEvent* mouseWheelEvents) {}
} // namespace blitz::platform