#pragma once

#include <GL/glew.h>
#include <core/TextureSpec.h>

namespace blitz
{
    GLenum toGLTextureType(const TextureType& textureType);
    GLenum toGLTextureFormat(const TextureFormat& textureFormat);
}