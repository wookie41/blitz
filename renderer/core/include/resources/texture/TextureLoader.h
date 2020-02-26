#pragma once

#include <resources/ResourceLocation.h>

namespace blitz
{
    class Texture;

    class TextureLoader
    {
      public:
      
        Texture* loadTexture(const ResourceLocation& location);

        ~TextureLoader() = default;
    };
} // namespace blitz