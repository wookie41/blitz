//
// Created by wookie on 27.08.19.
//
// The Device is an abstraction over the underlying OS, hardware,
// it is the provider of the most two crucial classes required to
// get a rendering context running (window, OpenGL/DirectX/Vulkan context).
//
// To avoid performance penalty, there is an static instance of the Device
// crated in file Globals.h

#pragma once

#include "blitzcommon/Utils.h"

#include "Window.h"

namespace blitz
{

    class Context;

    enum class DeviceErrorCode
    {
        NO_ERROR,

        //SDL2Device error codes
        SDL_INIT_ERROR,
        GLEW_INIT_ERROR
    };


    class Device : private NonCopyable
    {
      public:

        virtual Window* createWindow(const WindowDef& windowDef) const = 0;

        virtual Window* createWindow(const WindowDef &windowDef,
                                     Context* contextToShare) const = 0;
        virtual ~Device() = default;
    };
} // namespace blitz