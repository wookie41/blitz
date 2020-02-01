#include <blitzmemory/Heap.h>

static blitz::memory::Heap* heap;

void* operator new(std::size_t count) { return heap->allocate(count); }

void* operator new[](std::size_t count) { return heap->allocate(count); }

void operator delete(void* ptr) { heap->deallocate(ptr); }

void operator delete[](void* ptr) { heap->deallocate(ptr); }

namespace blitz::memory
{
    void InitMemory()
    {
	    heap = (Heap*)malloc(sizeof(Heap));
    	heap->Init();
    }

	void Heap::Init() {}
    void Heap::Shutdown() {}

    void* Heap::allocate(const size_t& amount)
    {
#ifdef USE_LIBC_MALLOC
        return malloc(amount);
#endif

        assert(0); // TODO
    }
    void* Heap::allocate8(const size_t& amount)
    {
#ifdef USE_LIBC_MALLOC
        return malloc(amount);
#endif

        assert(0); // TODO
    }

    void* Heap::allocate16(const size_t& amount)
    {
#ifdef USE_LIBC_MALLOC
        return malloc(amount);
#endif

        assert(0); // TODO
    }
    void* Heap::allocate32(const size_t& amount)
    {
#ifdef USE_LIBC_MALLOC
        return malloc(amount);
#endif
        assert(0); // TODO
    }
    void* Heap::allocate64(const size_t& amount)
    {
#ifdef USE_LIBC_MALLOC
        return malloc(amount);
#endif
        assert(0); // TODO
    }

    void Heap::Heap::deallocate(void* ptr)
    {
#ifdef USE_LIBC_MALLOC
        free(ptr);
#endif
    }
} // namespace blitz::memory