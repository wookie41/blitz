#include <core/Texture.h>
#include <core/ogl/texture/OpenGLTextureSampler.h>
#include <core/ogl/texture/OpenGLTextureUtils.h>

namespace blitz::ogl
{
    OpenGLTextureSampler::OpenGLTextureSampler(Texture* t) : TextureSampler(t) {}

    void OpenGLTextureSampler::bind()
    {
        const auto& glTextureType = toGLTextureType(texture->getTextureType());
        texture->bind();

    	if (isDirty & 0b00000001)
        {
            glTexParameteri(glTextureType, GL_TEXTURE_WRAP_S, wrapS);
        }
        if (isDirty & 0b00000010)
        {
            glTexParameteri(glTextureType, GL_TEXTURE_WRAP_T, wrapT);
        }
        if (isDirty & 0b00000011)
        {
            glTexParameteri(glTextureType, GL_TEXTURE_MIN_FILTER, minFilter);
        }

        if (isDirty & 0b00000100)
        {
            glTexParameteri(glTextureType, GL_TEXTURE_MAG_FILTER, magFilter);
        }

        isDirty = 0;
    }

    void OpenGLTextureSampler::unbind() { texture->unbind(); }

    void OpenGLTextureSampler::setTextureWrapHorizontal(const TextureWrap& textureWrap)
    {
        setWrapOption(0b00000001, wrapS, textureWrap);
    }

    void OpenGLTextureSampler::setTextureWrapVertical(const TextureWrap& textureWrap)
    {
        setWrapOption(0b00000010, wrapT, textureWrap);
    }

    void OpenGLTextureSampler::setMinFilter(const TextureFilter& textureFilter)
    {
        setFilterOption(0b00000011, minFilter, textureFilter);
    }
    void OpenGLTextureSampler::setMagFilter(const TextureFilter& textureFilter)
    {
        setFilterOption(0b00000100, magFilter, textureFilter);
    }

    void OpenGLTextureSampler::setWrapOption(uint8 dirty, GLenum& wrap, const TextureWrap& textureWrap)
    {
        switch (textureWrap)
        {
        case TextureWrap::CLAMP_TO_BORDER:
            wrap = GL_CLAMP_TO_BORDER;
            break;

        case TextureWrap::MIRRORED_REPEAT:
            wrap = GL_MIRRORED_REPEAT;
            break;

        case TextureWrap::REPEAT_CLAMP_TO_EDGE:
            wrap = GL_MIRRORED_REPEAT;
            break;
        }

        isDirty |= dirty;
    }

    void OpenGLTextureSampler::setFilterOption(uint8 dirty, GLenum& filter, const TextureFilter& textureFilter)
    {
        switch (textureFilter)
        {
        case TextureFilter::LINEAR:
            filter = GL_LINEAR;
            break;
        case TextureFilter::NEAREST:
            filter = GL_NEAREST;
            break;
        case TextureFilter::LINEAR_MIPMAP_LINEAR:
            filter = GL_LINEAR_MIPMAP_LINEAR;
            break;
        case TextureFilter::LINEAR_MIPMAP_NEAREST:
            filter = GL_LINEAR_MIPMAP_NEAREST;
            break;
        case TextureFilter::NEAREST_MIPMAP_LINEAR:
            filter = GL_NEAREST_MIPMAP_LINEAR;
            break;
        case TextureFilter::NEAREST_MIPMAP_NEAREST:
            filter = GL_NEAREST_MIPMAP_NEAREST;
            break;
        }
        isDirty |= dirty;
    }

} // namespace blitz::ogl