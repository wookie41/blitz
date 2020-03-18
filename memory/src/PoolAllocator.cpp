#include <blitzmemory/PoolAllocator.h>

namespace blitz::memory
{

    PoolAllocator::PoolAllocator(const size_t& size) : poolSize(size) { allocated = 0; }

    PoolAllocator::~PoolAllocator() { assert(pool == nullptr); }

    void PoolAllocator::init() { pool = (char*)malloc(poolSize); }

    void PoolAllocator::reset() { allocated = 0; }

    void PoolAllocator::shutdown() { free(pool); }

    void* PoolAllocator::memalloc(std::size_t count)
    {
        assert(count + allocated < poolSize);
        void* mem = pool + allocated;
        allocated += count;
        return mem;
    };

    void PoolAllocator::memfree(void* memory){
        // NOOP pool don't free individual chunks - use reset()
    };
} // namespace blitz::memory