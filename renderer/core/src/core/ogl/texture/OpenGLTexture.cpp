#include <core/ogl/texture/OpenGLTexture.h>
#include <loguru.hpp>
#include <core/ogl/texture/OpenGLTextureCreator.h>

#ifndef NDEBUG
static char ABSTRACT_TEXTURE_ERROR[] = "[OpenGL] Texture %d is not readable and writeable!";
#endif

namespace blitz
{
    OpenGLTexture::OpenGLTexture(const GLuint& textureID, const TextureSpec& textureSpec)
    : textureID(textureID), Texture(textureSpec)
    {
    }

    OpenGLTexture::OpenGLTexture(const OpenGLTexture& rhs) : Texture::Texture(rhs.textureSpec) { glGenTextures(1, &textureID); }

    OpenGLTexture::OpenGLTexture(OpenGLTexture&& rhs) noexcept : Texture(rhs.textureSpec)
    {
        this->textureID = rhs.textureID;
        rhs.textureID = UINT32_MAX;
    }

    OpenGLTexture& OpenGLTexture::operator=(OpenGLTexture&& rhs) noexcept
    {
        this->textureID = rhs.textureID;
        this->textureSpec = std::move(rhs.textureSpec);
        rhs.textureID = UINT32_MAX;
        return *this;
    }

    OpenGLTexture& OpenGLTexture::operator=(const OpenGLTexture& rhs)
    {
        glDeleteTextures(1, &textureID);
        textureSpec = rhs.textureSpec;
        textureID = GLTextureCreator::create(textureSpec);
        return *this;
    }

    void OpenGLTexture::bind()
    {
        GLenum glBindTarget;
        switch (textureSpec.textureType)
        {
        case TextureType::ONE_DIMENSIONAL:
            glBindTarget = GL_TEXTURE_1D;
            break;
        case TextureType::TWO_DIMENSIONAL:
            glBindTarget = GL_TEXTURE_2D;
            break;
        case TextureType::THREE_DIMENSIONAL:
            glBindTarget = GL_TEXTURE_3D;
            break;
        }

        glBindTexture(glBindTarget, textureID);
    }

    void OpenGLTexture::upload(void* data, size_t length) { DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID); }

    void* OpenGLTexture::download(void* destination)
    {
        DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID);
        return nullptr;
    }

    bool OpenGLTexture::isReadyToRead() const
    {
        DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID);
        return false;
    }

    OpenGLTexture::~OpenGLTexture()
    {
        if (textureId != UINT32_MAX)
        {
            glDeleteTextures(1, &textureID);
        }
    }
} // namespace blitz