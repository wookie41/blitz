#include <blitzmemory/Allocator.h>
#include <blitzmemory/OSHeapAllocator.h>

static blitz::memory::OSHeapAllocator heapAllocator;
thread_local blitz::memory::Allocator* allocator = &heapAllocator;

void resetAllocator() { allocator = &heapAllocator; }


void* operator new(std::size_t count) { return allocator->memalloc(count); }
void* operator new[](std::size_t count) { return allocator->memalloc(count); }

void operator delete(void* ptr) { allocator->memfree(ptr); }
void operator delete[](void* ptr) { allocator->memfree(ptr); }