#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    struct Range
    {
        size_t offset;
        size_t size;
    };

    struct Range2
    {
        size_t offsetX;
        size_t sizeX;
        size_t offsetY;
        size_t sizeY;
    };

    struct Range3
    {
        size_t offsetX;
        size_t sizeX;
        size_t offsetY;
        size_t sizeY;
        size_t offsetZ;
        size_t sizeZ;
    };


}