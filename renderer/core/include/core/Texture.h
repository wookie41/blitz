#pragma once

#include <blitzcommon/DataType.h>
#include <core/TextureSpec.h>
#include <core/Range.h>

namespace blitz
{
    class    Texture
    {
      public:
        virtual void upload(void* data) = 0;
        virtual void upload(void* data, const Range3& range) = 0;

        // download get the data from the graphics card that was previously uploaded with `upload` method
        // if the data pointer is not specified, the method should allocate a chunk big enough for the texture data
        // if no data was uploaded to the texture, the returned pointer should be null
        virtual void* download(void* destination, uint8 mipmapLevel) = 0;
        virtual void* download(void* destination, uint8 mipmapLevel, const Range3& range) = 0;

        // this method indicates if the texture can by read using the ptr return by `download` method
        // this may return false if the texture is handling transfers asynchronously using DMA or similar
        virtual bool isReadyToRead() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual uint64 getSizeInBytes() = 0;

        virtual ~Texture() = default;

        const TextureType& getTextureType() const;

    protected:
        explicit Texture(const TextureSpec& textureSpec);

        TextureSpec textureSpec;
        Range3 fullSizeRange;
    };
} // namespace blitz