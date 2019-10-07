#pragma once

#include <core/DataType.h>
#include <core/Color.h>

namespace blitz
{
    enum class TextureType
    {
        ONE_DIMENSIONAL,
        TWO_DIMENSIONAL,
        THREE_DIMENSIONAL
    };

    struct TextureSpec
    {
        TextureType textureType;
        Vector3f dimensions;
        uint8 mipmapLevel;
        ColorType colorType;
        DataType dataType;
        bool isAsyncTransferEnabled;
        bool isReadable;
        bool isWriteable;
    };
}