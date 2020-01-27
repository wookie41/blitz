#pragma once

#include <core/Max.h>
#include <core/TextureSpec.h>

namespace blitz
{
    class Texture;

    struct ShaderOutput
    {
        ShaderOutput() = default;

        uint16 outputIdx;
        Texture* texture;
        TextureFormat textureFormat;
        char* name;
    };
} // namespace blitz