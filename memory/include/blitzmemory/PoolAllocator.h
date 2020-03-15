#pragma once

#include <blitzmemory/Precompiled.h>
#include <blitzmemory/Allocator.h>

namespace blitz::memory
{
    class PoolAllocator : public Allocator
    {
      public:
        PoolAllocator(const size_t& size);
        virtual ~PoolAllocator();

        void init() override;
        void reset() override;
        void shutdown() override;

        void* memalloc(std::size_t count) override;
        void memfree(void* memory) override;

      private:
        char* pool;
        size_t poolSize;
        size_t allocated;
    };
} // namespace blitz::memory