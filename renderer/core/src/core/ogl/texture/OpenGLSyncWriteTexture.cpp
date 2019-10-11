#include <core/ogl/texture/OpenGLSyncWriteTexture.h>
#include <core/ogl/OpenGLDataType.h>
#include <loguru.hpp>

namespace blitz
{
    OpenGLSyncWriteTexture::OpenGLSyncWriteTexture(const GLuint& textureID, const TextureSpec& textureSpec)
    : OpenGLTexture(textureID, textureSpec)
    {
    }

    void OpenGLSyncWriteTexture::upload(void* data) { writeToTexture(data, fullSizeRange); }
    void OpenGLSyncWriteTexture::upload(void* data, const Range3& range) { writeToTexture(data, range); }

    void OpenGLSyncWriteTexture::writeToTexture(void* data, const Range3& range)
    {
        if (data == nullptr)
        {
            DLOG_F(ERROR, "[OpenGL] Can't upload to texture %d, the data pointer is null", textureID);

            return;
        }

        bind();
        switch (textureSpec.textureType)
        {
        case TextureType::ONE_DIMENSIONAL:
            glTexSubImage1D(glTextureType, textureSpec.mipmapLevel, range.offsetX, range.sizeX, glTextureFormat,
                            mapToGLDataType(textureSpec.dataType), data);
            break;
        case TextureType::TWO_DIMENSIONAL:
            glTexSubImage2D(glTextureType, textureSpec.mipmapLevel, range.offsetX, range.sizeX, range.offsetY,
                            range.sizeY, glTextureFormat, mapToGLDataType(textureSpec.dataType), data);
            break;
        case TextureType::THREE_DIMENSIONAL:
            glTexSubImage3D(glTextureType, textureSpec.mipmapLevel, range.offsetX, range.sizeX, range.offsetY, range.sizeY,
                            range.offsetZ, range.sizeZ, glTextureFormat, mapToGLDataType(textureSpec.dataType), data);
            break;
        }
        unbind();
    }
} // namespace blitz