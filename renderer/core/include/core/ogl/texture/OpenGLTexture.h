#pragma once

#include <GL/glew.h>
#include <core/Texture.h>

namespace blitz
{
    class OpenGLTexture : Texture
    {
        void upload(void* data, size_t length) override;
        void* download(void* destination) override;
        bool isReadyToRead() const override;

        void bind() override;

        OpenGLTexture(const OpenGLTexture& rhs);
        OpenGLTexture(OpenGLTexture&& rhs) noexcept;

        OpenGLTexture& operator=(const OpenGLTexture& rhs);
        OpenGLTexture& operator=(OpenGLTexture&& rhs) noexcept;

      public:
        ~OpenGLTexture() override;

      protected:
        OpenGLTexture(const GLuint& textureID, const TextureSpec& textureSpec);
        GLuint textureID = UINT32_MAX;
    };

} // namespace blitz