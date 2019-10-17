#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <cassert>
#include <core/sdl2/SDL2Device.h>


#include "loguru.hpp"

#include "core/RendererErrorCode.h"
#include "core/sdl2/SDL2Context.h"
#include "core/sdl2/SDL2Device.h"
#include "core/sdl2/SDL2Window.h"

namespace blitz
{

    SDL2Device::SDL2Device()
    {
        DLOG_F(INFO, "Initializing SDL2 device...");

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            DLOG_F(ERROR, "Failed to init SDL2 video module: %s", SDL_GetError());
            exit(RendererErrorCode::SDL2DEVICE_SDL_INIT_ERROR);
        }

        DLOG_F(INFO, "SDL2 initialized!");

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        auto tmpWindow = createWindow({});

        auto glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            DLOG_F(ERROR, "Failed to initialize GLEW: %s", glewGetErrorString(glewInitResult));
            exit(RendererErrorCode::SDL2DEVICE_GLEW_INIT_ERROR);
        }

        DLOG_F(INFO, "GLEW initialized!");
        DLOG_F(INFO, "SDL2Device initialized!");

        delete tmpWindow;
    }

    Window* SDL2Device::createWindow(const WindowDef& windowDef) const
    {
        auto sdlWindow = createSDLWindow(windowDef);
        auto context = SDL_GL_CreateContext(sdlWindow);

        if(context == nullptr)
        {
            DLOG_F(ERROR, "Failed to create context: %s", SDL_GetError());
            exit(RendererErrorCode::SDL2DEVICE_CONTEXT_CREATION_ERROR);
        }

        return new SDL2Window(sdlWindow, new SDL2Context(context), true);
    }

    Window* SDL2Device::createWindow(const WindowDef& windowDef, Context* contextToShare) const
    {
        auto context = dynamic_cast<SDL2Context*>(contextToShare);
        if (context == nullptr)
        {
            DLOG_F(ERROR, "Not an SDL context");
            exit(RendererErrorCode::SDL2DEVICE_NOT_SDL_CONTEXT);
        }

        auto sdlWindow = createSDLWindow(windowDef);
        return new SDL2Window(sdlWindow, context, false);
    }

    SDL2Device::~SDL2Device() { SDL_Quit(); }

    SDL_Window *SDL2Device::createSDLWindow(const WindowDef &windowDef) const
    {
        auto window = SDL_CreateWindow(windowDef.title, windowDef.x, windowDef.y,
                                       windowDef.width, windowDef.height,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
        if(window == nullptr)
        {
            DLOG_F(ERROR, "Failed to create window: %s", SDL_GetError());
            exit(RendererErrorCode::SDL2DEVICE_WINDOW_CREATION_ERROR);
        }

        return window;
    }
} // namespace blitz