#pragma once

#include <core/Precompiled.h>
#include <core/Color.h>
#include <core/Range.h>

namespace blitz
{
    enum class TextureType
    {
        ONE_DIMENSIONAL,
        TWO_DIMENSIONAL,
        THREE_DIMENSIONAL
    };

    enum class TextureFormat
    {
        RGB,
        RGBA,
        STENCIL,
        DEPTH,
        DEPTH_STENCIL
    };

    struct TextureSpec
    {
        TextureSpec() = default;
    	
        TextureType textureType;
        Vector3i dimensions;
        uint8 mipmapLevel;
        TextureFormat textureFormat;
        DataType dataType;
        bool isAsyncTransferEnabled;
        bool isReadable;
        bool isWriteable;

        //TODO this could be replaced with a DataSource in the future
        //TODO so we can stream textures and update them incrementally,
        //TODO as the data is coming from for example a network socket,
        //TODO or if we're streaming a really big texture from a disk
        unsigned char* data; // set to null if you only want to allocate the space for the texture

        TextureSpec(const TextureSpec& rhs) = default;
        TextureSpec(TextureSpec&& rhs) = default;
        TextureSpec& operator=(TextureSpec&& rhs) = default;
        TextureSpec& operator=(const TextureSpec& rhs) = default;
    };
}