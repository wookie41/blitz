#include <core/ogl/texture/OpenGLSyncReadTexture.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/texture/OpenGLTextureUtils.h>
#include <core/ogl/OpenGLDataType.h>
#include <loguru.hpp>

namespace blitz::ogl
{
    OpenGLSyncReadTexture::OpenGLSyncReadTexture(const GLuint& textureID, const TextureSpec& textureSpec)
    : OpenGLTexture(textureID, textureSpec)
    {
    }

    void* OpenGLSyncReadTexture::download(void* destination, uint8 mipmapLevel)
    {
        return readTexture(destination, mipmapLevel, fullSizeRange);
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
        glGetTextureSubImage(glTextureType, mipmapLevel, range.offsetX, range.offsetY, range.offsetZ, range.sizeX,
                             range.offsetY, range.sizeZ, glTextureFormat, mapToGLDataType(textureSpec.dataType), getSizeInBytes(), destination);
        unbind();

        return destination;
    }
} // namespace blitz::ogl