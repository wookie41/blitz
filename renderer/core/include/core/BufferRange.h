#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    class Buffer;

    struct BufferRange
    {
        Buffer* buffer;
        uint32 offset;
        uint32 size;
    };

}