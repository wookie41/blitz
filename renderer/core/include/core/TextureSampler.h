#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class Texture;

    enum class TextureWrap
    {
        REPEAT_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
        MIRRORED_REPEAT
    };

    enum class TextureFilter
    {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST,
        LINEAR_MIPMAP_LINEAR,
    };

    class TextureSampler : NonCopyable
    {
      public:

        Texture* getTexture() const;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void setTextureWrapHorizontal(const TextureWrap& textureWrap) = 0;
        virtual void setTextureWrapVertical(const TextureWrap& textureWrap) = 0;
        virtual void setMagFilter(const TextureFilter& textureFilter) = 0;
        virtual void setMinFilter(const TextureFilter& textureFilter) = 0;

        virtual ~TextureSampler() = default;

      protected:
        explicit TextureSampler(Texture* t);

        Texture* texture;
    };
} // namespace blitz