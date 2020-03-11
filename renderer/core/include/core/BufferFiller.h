#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class Buffer;

    struct FillArgs
    {
        void* data;
        size_t offset;
        size_t dataSizeInBytes;
        bool shouldInvalidate;
    };

    class BufferFiller : NonCopyable
    {
      public:
        virtual void fill(Buffer* buffer, const FillArgs& fillArgs) = 0;
    };
} // namespace blitz