#include <InMemoryTextureLoader.h>
#include <blitzcommon/HashUtils.h>
#include <loguru.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC
#define STBI_REALLOC
#define STBI_FREE

#include <core/Device.h>
#include <stb/stb_image.h>

namespace blitz
{
    extern Device* DEVICE;

    InMemoryTextureLoader::InMemoryTextureLoader(const BytesBuffer& buffer)
    : bytesBuffer(buffer), startingAddressAsInt((uintptr)buffer.dataLocation)
    {
    }

    blitz::Texture* blitz::InMemoryTextureLoader::load()
    {
        int width, height, numOfComponents;
        unsigned char* textureData = stbi_load_from_memory((unsigned char*)bytesBuffer.dataLocation, bytesBuffer.size,
                                                           &width, &height, &numOfComponents, 0);
        if (textureData == nullptr)
        {
            DLOG_F(ERROR, "Failed to load texture from memory: %s", stbi_failure_reason());
            return nullptr;
        }

        // TODO test with grey-scale bitmaps
        TextureSpec loadedTextureSpec{ TextureType::TWO_DIMENSIONAL,
                                       { static_cast<uint32>(width), static_cast<uint32>(height), 0 },
                                       1,
                                       numOfComponents == 3 ? TextureFormat::RGB : TextureFormat::RGBA,
                                       DataType::UBYTE,
                                       false,
                                       true,
                                       true,
                                       textureData };

        const auto texture = DEVICE->createTexture(loadedTextureSpec);
        stbi_image_free(textureData);
        return texture;
    }

    const ResourceID InMemoryTextureLoader::getID() const { return startingAddressAsInt; }
} // namespace blitz