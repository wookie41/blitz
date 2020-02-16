#include <platform/Precompiled.h>
#include <platform/event/SDLEventPooler.h>
#include <platform/input/SDLInputManager.h>

namespace blitz::platform
{
    SDLEventPooler::SDLEventPooler(SDLInputManager* inputHandler) : sdlInputManager(inputHandler) {}

    void SDLEventPooler::poolEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                sdlInputManager->handleKeyDownEvent((SDL_KeyboardEvent*)&event);
                break;
            case SDL_KEYUP:
                sdlInputManager->handleKeyUpEvent((SDL_KeyboardEvent*)&event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                sdlInputManager->handleMouseButtonDownEvent((SDL_MouseButtonEvent*)&event);
                break;
            case SDL_MOUSEBUTTONUP:
                sdlInputManager->handleMouseButtonUpEvent((SDL_MouseButtonEvent*)&event);
                break;
            case SDL_MOUSEMOTION:
                sdlInputManager->handleMouseMovementEvent((SDL_MouseMotionEvent*)&event);
                break;
            case SDL_MOUSEWHEEL:
                sdlInputManager->handleMouseWheelEvent((SDL_MouseWheelEvent*)&event);
                break;
            default:
                break;
            }
        }
    }


} // namespace blitz::platform
