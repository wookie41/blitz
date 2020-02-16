#include <platform/input/KeyboardState.h>
#include <platform/input/SDLInputManager.h>
#include <unordered_map>


namespace blitz::platform
{
    static std::unordered_map<SDL_Keycode, uint64> keyCodesMapping{ { SDLK_w, blitz::platform::KEY_W },
                                                                    { SDLK_s, blitz::platform::KEY_S },
                                                                    { SDLK_a, blitz::platform::KEY_A },
                                                                    { SDLK_d, blitz::platform::KEY_D } };

    const KeyboardState* SDLInputManager::getKeyboardState() const { return keyboardState; }
    const MouseState* SDLInputManager::getMouseState() const { return mouseState; }

    void SDLInputManager::handleKeyDownEvent(const SDL_KeyboardEvent* keyboardEvent)
    {
        setDown(keyboardState, keyCodesMapping[keyboardEvent->keysym.sym]);
    }

    void SDLInputManager::handleKeyUpEvent(const SDL_KeyboardEvent* keyboardEvent)
    {
        setDown(keyboardState, keyCodesMapping[keyboardEvent->keysym.sym]);
    }

    void SDLInputManager::handleMouseMovementEvent(const SDL_MouseMotionEvent* mouseMovementEvent) {}

    void SDLInputManager::handleMouseButtonDownEvent(const SDL_MouseButtonEvent* mouseButtonEvent) {}
    void SDLInputManager::handleMouseButtonUpEvent(const SDL_MouseButtonEvent* mouseButtonEvent) {}

    void SDLInputManager::handleMouseWheelEvent(const SDL_MouseWheelEvent* mouseWheelEvents) {}
} // namespace blitz::platform