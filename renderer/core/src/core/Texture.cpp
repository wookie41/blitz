#pragma once

#include <core/Texture.h>

namespace blitz
{
    blitz::Texture::Texture(const TextureSpec& textureSpec) : textureSpec(textureSpec)
    {
        fullSizeRange.offsetX = fullSizeRange.offsetY = fullSizeRange.offsetZ = 0;
        fullSizeRange.sizeX = textureSpec.dimensions.x;
        fullSizeRange.sizeY = textureSpec.dimensions.y;
        fullSizeRange.sizeZ = textureSpec.dimensions.z;
    }

    const TextureType& Texture::getTextureType() const { return textureSpec.textureType; }
} // namespace blitz