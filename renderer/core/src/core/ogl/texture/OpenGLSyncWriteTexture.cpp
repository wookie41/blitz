#include <core/ogl/texture/OpenGLSyncWriteTexture.h>
#include <core/ogl/OpenGLDataType.h>
#include <loguru.hpp>


namespace blitz::ogl
{
    OpenGLSyncWriteTexture::OpenGLSyncWriteTexture(const GLuint& texID, const TextureSpec& texSpec)
    : OpenGLTexture(texID, texSpec)
    {
    }

    void OpenGLSyncWriteTexture::upload(void* data) { writeToTexture(data, fullTextureRange); }
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
            glTexSubImage1D(glTextureType, textureSpec.mipmapLevel, 
						ToGLSize(range.offsetX), ToGLSize(range.sizeX),
                            glTextureFormat,
                            mapToGLDataType(textureSpec.dataType), data);
            break;
        case TextureType::TWO_DIMENSIONAL:
            glTexSubImage2D(glTextureType, textureSpec.mipmapLevel, 
							ToGLSize(range.offsetX), ToGLSize(range.offsetY),
                            ToGLSize(range.sizeX), ToGLSize(range.sizeY), glTextureFormat,
                            mapToGLDataType(textureSpec.dataType), data);
            break;
        case TextureType::THREE_DIMENSIONAL:
            glTexSubImage3D(glTextureType, textureSpec.mipmapLevel, 
							ToGLSize(range.offsetX), ToGLSize(range.sizeX), 
							ToGLSize(range.offsetY), ToGLSize(range.sizeY),
                            ToGLSize(range.offsetZ), ToGLSize(range.sizeZ), 
							glTextureFormat, mapToGLDataType(textureSpec.dataType), data);
            break;
        }

        glGenerateMipmap(glTextureType);
        unbind();
    }
} // namespace blitz::ogl