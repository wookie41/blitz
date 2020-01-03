#pragma once

#include <blitzcommon/DataType.h>

namespace blitz::platform::os
{
    const uint8 ACCESS_READ = 1;
    const uint8 ACCESS_WRITE = 2;
    const uint8 ACCESS_EXEC = 3;

    struct MemoryMappedFile
    {
        BytesBuffer buffer;
    };

    MemoryMappedFile mapFile(char* filePath, uint8 accessFlags);
}
