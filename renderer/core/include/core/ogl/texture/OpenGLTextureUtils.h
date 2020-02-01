#pragma once

#include <core/Precompiled.h>
#include <core/TextureSpec.h>

namespace blitz::ogl
{
    GLenum toGLTextureType(const TextureType& textureType);
    GLenum toGLTextureFormat(const TextureFormat& textureFormat);
}