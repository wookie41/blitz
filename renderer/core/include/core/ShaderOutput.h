#pragma once

#include <core/Max.h>
#include <core/Precompiled.h>
#include <core/TextureSpec.h>

namespace blitz
{
    class Texture;

    struct ShaderOutput
    {
        uint16 outputIdx;
        TextureFormat textureFormat;
        blitz::string name;
    };
} // namespace blitz