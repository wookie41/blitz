#include <core/ogl/texture/OpenGLSyncReadWriteTexture.h>

namespace blitz
{

    OpenGLSyncReadWriteTexture::OpenGLSyncReadWriteTexture(GLuint textureID, const TextureSpec& textureSpec)
    : OpenGLSyncReadTexture(textureID, textureSpec), OpenGLSyncWriteTexture(textureID, textureSpec)
    {
    }

    void OpenGLSyncReadWriteTexture::upload(void* data) { OpenGLSyncWriteTexture::upload(data); }

    void OpenGLSyncReadWriteTexture::upload(void* data, const Range3& range)
    {
        OpenGLSyncWriteTexture::upload(data, range);
    }

    void* OpenGLSyncReadWriteTexture::download(void* destination, uint8 mipmapLevel)
    {
        return OpenGLSyncReadTexture::download(destination, mipmapLevel);
    }

    void* OpenGLSyncReadWriteTexture::download(void* destination, uint8 mipmapLevel, const Range3& range)
    {
        return OpenGLSyncReadTexture::download(destination, mipmapLevel, range);
    }

    bool OpenGLSyncReadWriteTexture::isReadyToRead() const { return true; }
} // namespace blitz