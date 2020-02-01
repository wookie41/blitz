#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class Buffer;

    struct FillArgs
    {
        void* data;
        uint32 offset;
        uint32 dataSizeInBytes;
        bool shouldInvalidate;
    };

    class BufferFiller :NonCopyable
    {
    public:
        virtual void fill(Buffer* buffer, const FillArgs& fillArgs) = 0;
    };
} // namespace blitz