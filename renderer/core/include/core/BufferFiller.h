#pragma once

#include <cstdint>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class Buffer;

    struct FillArgs
    {
        void* data;
        std::size_t offset;
        std::size_t dataSize;
        bool shouldInvalidate;
    };

    class BufferFiller :NonCopyable
    {
    public:
        virtual void fill(Buffer* buffer, const FillArgs& fillArgs) = 0;
    };
} // namespace blitz