#pragma once

#include <core/Texture.h>

namespace blitz
{
    blitz::Texture::Texture(const TextureSpec& textureSpec)
    : textureType(textureSpec.textureType), dimensions(textureSpec.dimensions), mipmapLevel(textureSpec.mipmapLevel),
      colorType(textureSpec.colorType), dataType(textureSpec.dataType)
    {
    }
} // namespace blitz