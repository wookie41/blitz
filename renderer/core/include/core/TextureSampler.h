#pragma once

#include <blitzcommon/NonCopyable.h>

namespace blitz
{
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

    class Texture;

    class TextureSampler : NonCopyable
    {
      public:

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