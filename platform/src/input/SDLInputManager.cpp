#include <platform/input/KeyboardState.h>
#include <platform/input/MouseState.h>
#include <platform/input/SDLInputManager.h>
#include <unordered_map>


// TODO right now we'are ignoring wether mouse click occur in our window or not
// we probably should ignore click outside of our window, but the main task right now
// it to get the input system to work at all

namespace blitz::platform
{
    static std::unordered_map<SDL_Keycode, uint64> keyCodesMapping{ { SDLK_w, blitz::platform::KEY_W },
                                                                    { SDLK_s, blitz::platform::KEY_S },
                                                                    { SDLK_a, blitz::platform::KEY_A },
                                                                    { SDLK_d, blitz::platform::KEY_D },
                                                                    { SDLK_ESCAPE, blitz::platform::KEY_ESCAPE } };

    static std::unordered_map<uint32, uint32> mouseButtonMapping{ { SDL_BUTTON_LEFT, blitz::platform::LEFT_MOUSE_BUTTON },
                                                                  { SDL_BUTTON_RIGHT, blitz::platform::RIGHT_MOUSE_BUTTON } };

    const KeyboardState* SDLInputManager::getKeyboardState() const { return keyboardState; }
    const MouseState* SDLInputManager::getMouseState() const { return mouseState; }

    SDLInputManager::SDLInputManager()
    {
        keyboardState = new KeyboardState;
        mouseState = new MouseState;
    }

    void SDLInputManager::handleKeyDownEvent(const SDL_KeyboardEvent* keyboardEvent)
    {
        setDown(keyboardState, keyCodesMapping[keyboardEvent->keysym.sym]);
    }

    void SDLInputManager::handleKeyUpEvent(const SDL_KeyboardEvent* keyboardEvent)
    {
        setUp(keyboardState, keyCodesMapping[keyboardEvent->keysym.sym]);
    }

    void SDLInputManager::handleMouseMovementEvent(const SDL_MouseMotionEvent* mouseMovementEvent)
    {
        mouseState->absolutePos.x = mouseMovementEvent->x;
        mouseState->absolutePos.y = mouseMovementEvent->y;

        mouseState->relativePos.x = mouseMovementEvent->xrel;
        mouseState->relativePos.y = mouseMovementEvent->yrel;
    }

    void SDLInputManager::handleMouseButtonDownEvent(const SDL_MouseButtonEvent* mouseButtonEvent)
    {
        setDown(mouseState, mouseButtonMapping[mouseButtonEvent->button]);
    }

    void SDLInputManager::handleMouseButtonUpEvent(const SDL_MouseButtonEvent* mouseButtonEvent)
    {
        setUp(mouseState, mouseButtonMapping[mouseButtonEvent->button]);
    }

    void SDLInputManager::handleMouseWheelEvent(const SDL_MouseWheelEvent* mouseWheelEvent)
    {
        mouseState->wheelProgress += mouseWheelEvent->y;
    }

    SDLInputManager::~SDLInputManager() 
    {
        delete keyboardState;
        delete mouseState;
    }

} // namespace blitz::platform
