#pragma once

#include <core/ogl/texture/OpenGLTexture.h>

namespace blitz
{
    class OpenGLSyncReadTexture : public OpenGLTexture
    {
        friend class OpenGLContext;

      public:
        OpenGLSyncReadTexture(OpenGLSyncReadTexture&& rhs) = default;
        OpenGLSyncReadTexture(const OpenGLSyncReadTexture& rhs) = default;

        OpenGLSyncReadTexture& operator=(const OpenGLSyncReadTexture& rhs) = default;
        OpenGLSyncReadTexture& operator=(OpenGLSyncReadTexture&& rhs) = default;

      private:
        void* download(void* destination, uint8 mipmapLevel) override;

        bool isReadyToRead() const override;

      protected:
        OpenGLSyncReadTexture(const GLuint& textureID, const TextureSpec& textureSpec);
    };
} // namespace blitz