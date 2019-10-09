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
        Vector3i dimensions;
        uint8 mipmapLevel;
        ColorType colorType;
        DataType dataType;
        bool isAsyncTransferEnabled;
        bool isReadable;
        bool isWriteable;
        void* data; //set to null if you only want to allocate the space for the texture

        TextureSpec(const TextureSpec& rhs) = default;
        TextureSpec(TextureSpec&& rhs) = default;
        TextureSpec& operator=(TextureSpec&& rhs) = default;
        TextureSpec& operator=(const TextureSpec& rhs) = default;
    };
}