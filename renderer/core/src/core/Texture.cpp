#pragma once

#include <core/Texture.h>

namespace blitz
{
    blitz::Texture::Texture(const TextureSpec& spec) : textureSpec(spec)
    {
        fullTextureRange =
        {
        	0, (size_t)textureSpec.dimensions.x,
        	0, (size_t)textureSpec.dimensions.y,
        	0, (size_t)textureSpec.dimensions.z
        };
    }

    const TextureType& Texture::getTextureType() const { return textureSpec.textureType; }
} // namespace blitz