#include <core/ogl/texture/OpenGLSyncReadWriteTexture.h>

namespace blitz::ogl
{

    OpenGLSyncReadWriteTexture::OpenGLSyncReadWriteTexture(GLuint textureID, const TextureSpec& textureSpec)
    : OpenGLTexture(textureID, textureSpec), readInterface(textureID, textureSpec), writeInterface(textureID, textureSpec)
    {
    }

    void OpenGLSyncReadWriteTexture::upload(void* data) { writeInterface.upload(data); }

    void OpenGLSyncReadWriteTexture::upload(void* data, const Range3& range) { writeInterface.upload(data, range); }

    void* OpenGLSyncReadWriteTexture::download(void* destination, uint8 mipmapLevel)
    {
        return readInterface.download(destination, mipmapLevel);
    }

    void* OpenGLSyncReadWriteTexture::download(void* destination, uint8 mipmapLevel, const Range3& range)
    {
        return readInterface.download(destination, mipmapLevel, range);
    }

    bool OpenGLSyncReadWriteTexture::isReadyToRead() const { return true; }

    OpenGLSyncReadWriteTexture::~OpenGLSyncReadWriteTexture()
    {
        readInterface.textureID = writeInterface.textureID = UINT32_MAX;
    }
} // namespace blitz::ogl