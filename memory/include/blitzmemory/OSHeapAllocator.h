#pragma once

#include <blitzmemory/Allocator.h>

namespace blitz::memory
{
    class OSHeapAllocator : public Allocator
    {
      public:
        OSHeapAllocator() = default;
        virtual ~OSHeapAllocator() = default;

        void init() override;
        void reset() override;
        void shutdown() override;

        void* memalloc(std::size_t count) override;
        void memfree(void* memory) override;
    };
} // namespace blitz::memory