#pragma once

#include <GL/glew.h>
#include <core/Texture.h>

namespace blitz
{
    class OpenGLTexture : public Texture
    {
      public:
        OpenGLTexture(const OpenGLTexture& rhs);
        OpenGLTexture(OpenGLTexture&& rhs) noexcept;

        OpenGLTexture& operator=(const OpenGLTexture& rhs);
        OpenGLTexture& operator=(OpenGLTexture&& rhs) noexcept;

        uint64 getSizeInBytes() override;

        ~OpenGLTexture() override;

      protected:
        OpenGLTexture(const GLuint& textureID, const TextureSpec& textureSpec);

        GLuint textureID = UINT32_MAX;
        GLenum glTextureType;
        GLenum glTextureFormat;

      private:
        void upload(void* data) override;
        void* download(void* destination, uint8 mipMapLevel) override;
        bool isReadyToRead() const override;

        void bind() override;
    };

} // namespace blitz