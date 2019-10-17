#include <core/ogl/texture/OpenGLTextureUtils.h>

namespace blitz
{
    GLenum toGLTextureType(const TextureType& textureType)
    {
        switch (textureType)
        {
            case TextureType::ONE_DIMENSIONAL:
                return GL_TEXTURE_1D;
            case TextureType::TWO_DIMENSIONAL:
                return GL_TEXTURE_2D;
            case TextureType::THREE_DIMENSIONAL:
                return GL_TEXTURE_3D;
        }
    }

    GLenum toGLTextureFormat(const TextureFormat& textureFormat)
    {
        switch (textureFormat)
        {
            case TextureFormat::RGB:
                return GL_RGB;
            case TextureFormat::RGBA:
                return GL_RGBA;
            case TextureFormat::STENCIL:
                return GL_STENCIL_INDEX;
            case TextureFormat::DEPTH:
                return GL_DEPTH_COMPONENT;
            case TextureFormat::DEPTH_STENCIL:
                return GL_DEPTH_STENCIL;
        }
    }
}