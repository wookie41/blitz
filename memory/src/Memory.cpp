#include <blitzmemory/Allocator.h>
#include <blitzmemory/OSHeapAllocator.h>

namespace blitz::memory
{
    static OSHeapAllocator heapAllocator;
    thread_local Allocator* allocator = &heapAllocator;

    void resetAllocator() { allocator = &heapAllocator; }

} // namespace blitz::memory::

void* operator new(std::size_t count) { return blitz::memory::allocator->memalloc(count); }
void* operator new[](std::size_t count) { return blitz::memory::allocator->memalloc(count); }

void operator delete(void* ptr) { blitz::memory::allocator->memfree(ptr); }
void operator delete[](void* ptr) { blitz::memory::allocator->memfree(ptr); }