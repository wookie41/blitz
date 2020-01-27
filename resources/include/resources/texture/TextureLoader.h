#pragma once

#include <resources/ResourceLoader.h>
#include <core/Texture.h>

namespace blitz
{	
    class TextureLoader : public ResourceLoader<Texture>
    {
      public:
        explicit TextureLoader(const ResourceLocation& location);
    };
} // namespace blitz