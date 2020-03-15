#pragma once

#include <blitzmemory/Precompiled.h>

namespace blitz::memory
{
    // TODO we can actually make it copyable in future to copy whole regions of memoery
    class Allocator : public NonCopyable
    {
      public:
        Allocator() = default;
        virtual ~Allocator() = default;

        virtual void init() = 0;
        virtual void reset() = 0;
        virtual void shutdown() = 0;

        virtual void* memalloc(std::size_t count) = 0;
        virtual void memfree(void* memory) = 0;
    };
} // namespace blitz::memory