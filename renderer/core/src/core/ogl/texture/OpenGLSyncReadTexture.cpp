#include <core/ogl/texture/OpenGLSyncReadTexture.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <loguru.hpp>
#include <core/ogl/texture/OpenGLTextureUtils.h>

namespace blitz
{
    OpenGLSyncReadTexture::OpenGLSyncReadTexture(const GLuint& textureID, const TextureSpec& textureSpec)
    : OpenGLTexture(textureID, textureSpec)
    {
    }

    void* OpenGLSyncReadTexture::download(void* destination, uint8 mipmapLevel)
    {
        if (mipmapLevel > textureSpec.mipmapLevel)
        {
            DLOG_F(ERROR, "[OpenGL] Can't download texture %d at mipmap %d, it's mipmap level is %d", textureID,
                   mipmapLevel, textureSpec.mipmapLevel);
            return nullptr;
        }

        glBindTexture(glTextureType, textureID);

        if (destination == nullptr)
        {
            destination = malloc(getSizeInBytes());
        }

        glGetTexImage(glTextureType, mipmapLevel, glTextureFormat, glTextureType, destination);
        return destination;
    }

    bool OpenGLSyncReadTexture::isReadyToRead() const { return true; }
} // namespace blitz