#include <core/ogl/OpenGLDataType.h>
#include <core/ogl/texture/OpenGLTexture.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/texture/OpenGLTextureUtils.h>
#include <loguru.hpp>

#ifndef NDEBUG
static char ABSTRACT_TEXTURE_ERROR[] = "[OpenGL] Texture %d is not readable and writeable!";
#endif

namespace blitz
{
    OpenGLTexture::OpenGLTexture(const GLuint& textureID, const TextureSpec& textureSpec)
    : textureID(textureID), glTextureFormat(toGLTextureFormat(textureSpec.textureFormat)),
      glTextureType(toGLTextureType(textureSpec.textureType)), Texture(textureSpec)
    {
    }

    OpenGLTexture::OpenGLTexture(const OpenGLTexture& rhs) : Texture::Texture(rhs.textureSpec)
    {
        textureID = OpenGLTextureCreator::create(textureSpec);
    }

    OpenGLTexture::OpenGLTexture(OpenGLTexture&& rhs) noexcept : Texture(rhs.textureSpec)
    {
        textureID = rhs.textureID;
        rhs.textureID = UINT32_MAX;
    }

    OpenGLTexture& OpenGLTexture::operator=(OpenGLTexture&& rhs) noexcept
    {
        textureID = rhs.textureID;
        textureSpec = std::move(rhs.textureSpec);
        glTextureType = rhs.glTextureType;
        glTextureFormat = rhs.glTextureFormat;
        rhs.textureID = UINT32_MAX;
        return *this;
    }

    OpenGLTexture& OpenGLTexture::operator=(const OpenGLTexture& rhs)
    {
        glDeleteTextures(1, &textureID);
        textureSpec = rhs.textureSpec;
        textureID = OpenGLTextureCreator::create(textureSpec);
        glTextureType = rhs.glTextureType;
        glTextureFormat = rhs.glTextureFormat;
        return *this;
    }

    void OpenGLTexture::bind()
    {
        glBindTexture(glTextureType, textureID);
    }


    void OpenGLTexture::unbind()
    {
        glBindTexture(glTextureType, 0);
    }

    void OpenGLTexture::upload(void* data) { DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID); }
    void OpenGLTexture::upload(void* data, const Range3& range) { upload(data); }

    void* OpenGLTexture::download(void* destination, uint8 mipmapLevel)
    {
        DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID);
        return nullptr;
    }

    void* OpenGLTexture::download(void* destination, uint8 mipmapLevel, const Range3& range)
    {
        return download(destination, mipmapLevel);
    }

    bool OpenGLTexture::isReadyToRead() const
    {
        DLOG_F(ERROR, ABSTRACT_TEXTURE_ERROR, textureID);
        return false;
    }

    OpenGLTexture::~OpenGLTexture()
    {
        if (textureID != UINT32_MAX)
        {
            glDeleteTextures(1, &textureID);
        }
    }

    uint64 OpenGLTexture::getSizeInBytes()
    {
        const auto& sizeInBytes = getSizeInBytesFor(textureSpec.dataType);
        switch (textureSpec.textureType)
        {
        case TextureType::ONE_DIMENSIONAL:
            return textureSpec.dimensions.x * sizeInBytes;
        case TextureType::TWO_DIMENSIONAL:
            return textureSpec.dimensions.x * textureSpec.dimensions.y * sizeInBytes;
        case TextureType::THREE_DIMENSIONAL:
            return textureSpec.dimensions.x * textureSpec.dimensions.y * textureSpec.dimensions.z * sizeInBytes;
        }
    }
} // namespace blitz