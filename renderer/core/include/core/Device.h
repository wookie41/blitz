//
// Created by wookie on 27.08.19.
//
// The Device is an abstraction over the underlying OS, hardware,
// it is the provider of the most two crucial classes required to
// get a rendering context running (window, OpenGL/DirectX/Vulkan context).
//
// To avoid performance penalty, there is an static instance of the Device
// crated in file Globals.h
// You can change the Device's implementation using build the build flag:
//
// TODO

#pragma once

#include "blitzcommon/Utils.h"

#include "mathfu/constants.h"

#include "core/Context.h"
#include "core/Window.h.h"

namespace blitz
{
    class Device : private NonCopyable
    {
        virtual Context* createContext() = 0;

        virtual Window* createWindow(const WindowDef& windowDef) = 0;

        virtual Window* createWindowWithContext(const WindowDef& windowDef,
                                                const Context& context) = 0;
    };
} // namespace blitz