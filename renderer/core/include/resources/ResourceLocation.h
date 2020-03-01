#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    struct ResourceLocation
    {
        void* locationInMemory;
        char* pathToFile;
        size_t sizeInBytes;
    };
} // namespace blitz