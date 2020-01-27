#include <core/ogl/texture/OpenGLSyncReadTexture.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/OpenGLDataType.h>
#include <loguru.hpp>

namespace blitz::ogl
{
    OpenGLSyncReadTexture::OpenGLSyncReadTexture(const GLuint& texID, const TextureSpec& texSpec)
    : OpenGLTexture(texID, texSpec)
    {
    }

    void* OpenGLSyncReadTexture::download(void* destination, uint8 mipmapLevel)
    {
        return readTexture(destination, mipmapLevel, fullTextureRange);
    }

    void* OpenGLSyncReadTexture::download(void* destination, uint8 mipmapLevel, const Range3& range)
    {
        return readTexture(destination, mipmapLevel, range);
    }

    bool OpenGLSyncReadTexture::isReadyToRead() const { return true; }

    void* OpenGLSyncReadTexture::readTexture(void* destination, uint8 mipmapLevel, const Range3& range)
    {
        if (mipmapLevel > textureSpec.mipmapLevel)
        {
            DLOG_F(ERROR, "[OpenGL] Can't download texture %d at mipmap %d, it's mipmap level is %d", textureID,
                   mipmapLevel, textureSpec.mipmapLevel);
            return nullptr;
        }

        if (destination == nullptr)
        {
            destination = malloc(getSizeInBytes());
        }

        bind();
        glGetTextureSubImage(glTextureType, mipmapLevel, 
							ToGLSize(range.offsetX), ToGLSize(range.offsetY), ToGLSize(range.offsetZ), 
							ToGLSize(range.sizeX), ToGLSize(range.sizeY), ToGLSize(range.sizeZ), 
							glTextureFormat, mapToGLDataType(textureSpec.dataType), ToGLSize(getSizeInBytes()), destination);
        unbind();

        return destination;
    }
} // namespace blitz::ogl