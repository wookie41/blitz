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

#include <blitzcommon/NonCopyable.h>
#include <core/ShaderSource.h>
#include <core/Window.h>
#include <core/TextureSpec.h>
namespace blitz
{
    class Context;
    class Shader;
    class Texture;

    class Device : private NonCopyable
    {
      public:
        virtual Window* createWindow(const WindowDef& windowDef) const = 0;

        virtual Window* createWindow(const WindowDef& windowDef, Context* contextToShare) const = 0;

        virtual Shader* createShader(const ShaderSource& shaderSource) const = 0;

        virtual Texture* createTexture(const TextureSpec& textureSpec) const = 0;

        virtual ~Device() = default;
    };
} // namespace blitz