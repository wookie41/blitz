#pragma once

#include <core/Texture.h>

namespace blitz
{
    Texture::Texture(const TextureSpec& spec) : textureSpec(spec)
    {
        fullTextureRange = { 0, (size_t)textureSpec.dimensions.x, 0, (size_t)textureSpec.dimensions.y,
                             0, (size_t)textureSpec.dimensions.z };
        texSize = { (int32)fullTextureRange.sizeX, (int32)fullTextureRange.sizeY, (int32)fullTextureRange.sizeZ };
    }

    const Vector3i& Texture::getSize() const { return texSize; }
    const TextureType& Texture::getTextureType() const { return textureSpec.textureType; }
} // namespace blitz