#pragma once

#include <cstdint>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class Buffer;

    struct FillArgs
    {
        void* data;
        std::uint32_t offset;
        std::uint32_t dataSize;
        bool shouldInvalidate;
    };

    class BufferFiller :NonCopyable
    {
    public:
        virtual void fill(Buffer* buffer, const FillArgs& fillArgs) = 0;
    };
} // namespace blitz