#pragma once

#include <GL/glew.h>
#include <blitzcommon/DataType.h>
#include <core/TextureSampler.h>

namespace blitz::ogl
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

    public: //todo should this be private???
        explicit OpenGLTextureSampler(Texture* t);
    };
} // namespace blitz::ogl