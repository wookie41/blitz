#include <core/ogl/texture/GLTexture.h>
#include <loguru.hpp>

#ifndef NDEBUG
static char ABSTRACT_TEXTURE_ERROR[] = "[OpenGL] Texture %d is not readable and writeable!";
#endif

namespace blitz
{
    GLTexture::GLTexture(GLuint textureID, const TextureSpec& textureSpec) : textureID(textureID), Texture(textureSpec)
    {
    }

    void GLTexture::bind()
    {
        GLenum glBindTarget;
        switch (textureType)
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

    void GLTexture::upload(void* data, size_t length) { DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID); }

    void* GLTexture::download(void* destination)
    {
        DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID);
        return nullptr;
    }

    bool GLTexture::isReadyToRead() const
    {
        DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID);
        return false;
    }
} // namespace blitz