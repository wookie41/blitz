#pragma once

#include <GL/glew.h>
#include <core/Texture.h>

namespace blitz::ogl
{
    class OpenGLTexture : public Texture
    {
      public:

        OpenGLTexture(const OpenGLTexture& rhs);
        OpenGLTexture(OpenGLTexture&& rhs) noexcept;

        OpenGLTexture& operator=(const OpenGLTexture& rhs);
        OpenGLTexture& operator=(OpenGLTexture&& rhs) noexcept;

        void upload(void* data) override;
        void upload(void* data, const Range3& range) override;

        void* download(void* destination, uint8 mipMapLevel) override;
        void* download(void* destination, uint8 mipMapLevel, const Range3& range) override;

        bool isReadyToRead() const override;

        uint64 getSizeInBytes() override;
        GLuint getTextureID() const;

        ~OpenGLTexture() override;

        void bind() override;
        void unbind() override;

    protected:
        OpenGLTexture(const GLuint& texID, const TextureSpec& texSpec);

        GLuint textureID = UINT32_MAX;
        GLenum glTextureType;
        GLenum glTextureFormat;
    };
} // namespace blitz::ogl