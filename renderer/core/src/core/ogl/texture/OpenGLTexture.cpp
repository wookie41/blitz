#include <core/ogl/OpenGLDataType.h>
#include <core/ogl/texture/OpenGLTexture.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/texture/OpenGLTextureUtils.h>
#include <loguru.hpp>

#ifndef NDEBUG
static char ABSTRACT_TEXTURE_ERROR[] = "[OpenGL] Texture %d is not readable and writeable!";
#endif

namespace blitz::ogl
{
    OpenGLTexture::OpenGLTexture(const GLuint& textureID, const TextureSpec& textureSpec)
    : textureID(textureID), glTextureFormat(toGLTextureFormat(textureSpec.textureFormat)),
      glTextureType(toGLTextureType(textureSpec.textureType)), Texture(textureSpec)
    {
    }

    OpenGLTexture::OpenGLTexture(const OpenGLTexture& rhs) : Texture::Texture(rhs.textureSpec)
    {
        textureID = OpenGLTextureCreator::createGLTexture(textureSpec);
        glTextureFormat = rhs.glTextureFormat;
        glTextureType = rhs.glTextureType;
    }

    OpenGLTexture::OpenGLTexture(OpenGLTexture&& rhs) noexcept : Texture(rhs.textureSpec)
    {
        textureID = rhs.textureID;
        glTextureFormat = rhs.glTextureFormat;
        glTextureType = rhs.glTextureType;
    	
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
        textureID = OpenGLTextureCreator::createGLTexture(textureSpec);
        glTextureType = rhs.glTextureType;
        glTextureFormat = rhs.glTextureFormat;
        return *this;
    }

    void OpenGLTexture::bind() { glBindTexture(glTextureType, textureID); }


    void OpenGLTexture::unbind() { glBindTexture(glTextureType, 0); }

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
        const auto sizeInBytes = ToUint64(textureSpec.dataType);
        const auto sizeX = ToUint64(textureSpec.dimensions.x);
        const auto sizeY = ToUint64(textureSpec.dimensions.y);
        const auto sizeZ = ToUint64(textureSpec.dimensions.z);
    	
        switch (textureSpec.textureType)
        {
        case TextureType::ONE_DIMENSIONAL:
            return sizeX * sizeInBytes;
        case TextureType::TWO_DIMENSIONAL:
            return sizeX * sizeY * sizeInBytes;
        case TextureType::THREE_DIMENSIONAL:
            return sizeX * sizeY * sizeZ * sizeInBytes;
        }
    	
        assert(1 == 0);
        return 0;
    }

    GLuint OpenGLTexture::getTextureID() const { return textureID; }
} // namespace blitz::ogl