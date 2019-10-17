#pragma once

#include <GL/glew.h>
#include <core/DataType.h>
#include <core/TextureSampler.h>

namespace blitz
{
    class OpenGLTextureSampler : public TextureSampler
    {
      public:
        void bind() override;
        void unbind() override;

        void setTextureWrapHorizontal(const TextureWrap& textureWrap) override;
        void setTextureWrapVertical(const TextureWrap& textureWrap) override;

        void setMagFilter(const TextureFilter& textureFilter) override;
        void setMinFilter(const TextureFilter& textureFilter) override;

      private:
        uint8 isDirty;

        GLenum glTextureType;
        GLenum wrapS;
        GLenum wrapT;

        GLenum minFilter;
        GLenum magFilter;

        void setWrapOption(uint8 dirty, GLenum& wrap, const TextureWrap& textureWrap);
        void setFilterOption(uint8 dirty, GLenum& filter, const TextureFilter& textureFilter);

        explicit OpenGLTextureSampler(Texture* texture);
    };
} // namespace blitz