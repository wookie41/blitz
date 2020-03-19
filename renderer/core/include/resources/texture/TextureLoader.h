#pragma once

#include <resources/ResourceLocation.h>

namespace blitz
{
    class Texture;

    Texture* loadTexture(const ResourceLocation& location);

} // namespace blitz