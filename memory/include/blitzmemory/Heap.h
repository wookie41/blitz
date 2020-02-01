#pragma once

#include <blitzmemory/Precompiled.h>

namespace blitz::memory
{
    class Heap: public NonCopyable
    {
      public:

    	Heap() = default;
        ~Heap() = default;

    	void Init();
        void Shutdown();
    	
        void* allocate(const size_t& amount);
        void* allocate8(const size_t& amount); // allocate memory and align it to 1 byte
        void* allocate16(const size_t& amount); // allocate memory and align it to 1 byte
        void* allocate32(const size_t& amount); // allocate memory and align it to 1 byte
        void* allocate64(const size_t& amount); // allocate memory and align it to 1 byte
        void deallocate(void* ptr);
    };
} // namespace blitz::memory