#define STB_IMAGE_IMPLEMENTATION

#include <resources/texture/TextureLoader.h>

#include <blitzcommon/HashUtils.h>
#include <core/Device.h>
#include <loguru.hpp>
#include <stb/stb_image.h>

extern blitz::Device* BLITZ_DEVICE;

namespace blitz
{
    Texture* TextureLoader::loadTexture(const ResourceLocation& resourceLocation)
    {
        unsigned char* textureData = nullptr;
        int width, height, numOfChannels;
        if (resourceLocation.locationInMemory != nullptr)
        {
            DLOG_F(INFO, "Loading a texture from adderss %p", resourceLocation.locationInMemory);

            textureData = stbi_load_from_memory((stbi_uc*)resourceLocation.locationInMemory,
                                                resourceLocation.sizeInBytes, &width, &height, &numOfChannels, 0);
        }
        else
        {
            DLOG_F(INFO, "Loading a texture from file %s", resourceLocation.pathToFile);

            textureData = stbi_load(resourceLocation.pathToFile, &width, &height, &numOfChannels, 0);
        }

        assert(textureData != nullptr);
        Vector3i textureDimensions;
        textureDimensions.x = width;
        textureDimensions.y = height;

        TextureSpec textureSpec;
        textureSpec.textureType = TextureType::TWO_DIMENSIONAL;
        textureSpec.dimensions = textureDimensions;
        textureSpec.isAsyncTransferEnabled = false;
        textureSpec.isReadable = textureSpec.isWriteable = true;
        textureSpec.mipmapLevel = 0;
        textureSpec.textureFormat = numOfChannels == 3 ? TextureFormat::RGB : TextureFormat::RGBA;
        textureSpec.data = textureData;
        textureSpec.dataType = DataType::UBYTE;

        const auto texturePtr = BLITZ_DEVICE->createTexture(textureSpec);
        assert(texturePtr != nullptr);
        stbi_image_free(textureData);
        textureSpec.data = nullptr;

        return texturePtr;
    }
} // namespace blitz