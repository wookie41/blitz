#pragma once

#include <cstdint>

namespace blitz
{
    enum class BufferBindTarget
    {
        VERTEX,
        ELEMENT
    };

    class Buffer
    {
      public:
        virtual uint64_t getSize() const;
        virtual void put(void* data, const uint64_t len);
        virtual void get(void* buffer, const uint64_t len);
    };
} // namespace blitz