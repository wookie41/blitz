#pragma once

#include <core/ogl/texture/OpenGLTexture.h>

namespace blitz::ogl
{
    class OpenGLSyncReadTexture : public OpenGLTexture
    {
        friend class OpenGLDevice;
        friend class OpenGLSyncReadWriteTexture;

      public:
        OpenGLSyncReadTexture(OpenGLSyncReadTexture&& rhs) = default;
        OpenGLSyncReadTexture(const OpenGLSyncReadTexture& rhs) = default;

        OpenGLSyncReadTexture& operator=(const OpenGLSyncReadTexture& rhs) = default;
        OpenGLSyncReadTexture& operator=(OpenGLSyncReadTexture&& rhs) = default;

        void* download(void* destination, uint8 mipmapLevel) override;
        void* download(void* destination, uint8 mipmapLevel, const Range3& range) override;

        bool isReadyToRead() const override;

      protected:
        void* readTexture(void* destination, uint8 mipmapLevel, const Range3& range);
        OpenGLSyncReadTexture(const GLuint& texID, const TextureSpec& texSpec);
    };
} // namespace blitz::ogl