#include <blitzmemory/OSHeapAllocator.h>

namespace blitz::memory
{
    void OSHeapAllocator::init() {}
    void OSHeapAllocator::reset() {}
    void OSHeapAllocator::shutdown(){};

    void* OSHeapAllocator::memalloc(std::size_t count) { return malloc(count); };
    void OSHeapAllocator::memfree(void* memory) { free(memory); };
} // namespace blitz::memory