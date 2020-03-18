#pragma once

#include <blitzmemory/Precompiled.h>
#include <blitzmemory/OSHeapAllocator.h>

namespace blitz::memory
{
    class Allocator;

    void setThreadAllocator(Allocator* alloc);
    void resetThreadAllocator();
} // namespace blitz::memory