#pragma once

#include <core/DataType.h>
#include <core/TextureSpec.h>

namespace blitz
{
    class Texture
    {
      public:
        virtual void upload(void* data, size_t length) = 0;

        // download get the data from the graphics card that was previously uploaded with `upload` method
        // if the data pointer is not specified, the method should allocate a chunk big enough for the texture data
        // if no data was uploaded to the texture, the returned pointer should be null
        virtual void* download(void* destination) = 0;

        // this method indicates if the texture can by read using the ptr return by `download` method
        // this may return false if the texture is handling transfers asynchronously using DMA or similar
        virtual bool isReadyToRead() const = 0;

        virtual void bind() = 0;

        virtual ~Texture() = default;

    protected:
        explicit Texture(const TextureSpec& textureSpec);

        TextureSpec textureSpec;
    };
} // namespace blitz