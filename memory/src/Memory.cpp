#include <blitzmemory/Memory.h>
#include <blitzmemory/Allocator.h>
#include <blitzmemory/OSHeapAllocator.h>

namespace blitz::memory
{
    static OSHeapAllocator heapAllocator;
    thread_local Allocator* threadAllocator = nullptr;

    void setThreadAllocator(Allocator* alloc) { threadAllocator = alloc; }

    void resetThreadAllocator() { threadAllocator = &heapAllocator; }

} // namespace blitz::memory

void* operator new(std::size_t count)
{
    if (blitz::memory::threadAllocator == nullptr)
    {
        return malloc(count);
    }

    return blitz::memory::threadAllocator->memalloc(count);
}

void* operator new[](std::size_t count)
{
    if (blitz::memory::threadAllocator == nullptr)
    {
        return malloc(count);
    }
    return blitz::memory::threadAllocator->memalloc(count);
}

void operator delete(void* ptr)
{
    if (blitz::memory::threadAllocator == nullptr)
    {
        free(ptr);
        return;
    }
    blitz::memory::threadAllocator->memfree(ptr);
}

void operator delete[](void* ptr)
{
    if (blitz::memory::threadAllocator == nullptr)
    {
        free(ptr);
        return;
    }

    blitz::memory::threadAllocator->memfree(ptr);
}