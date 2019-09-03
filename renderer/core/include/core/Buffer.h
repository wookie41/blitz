#pragma once

#include <cstdint>

namespace blitz
{
    const uint8_t NUM_OF_BUFFER_BIND_TARGETS = 2;

    enum class BufferBindTarget
    {
        VERTEX,
        ELEMENT,
        WRITE
    };

    enum class UsageHint
    {
        STATIC,
        STREAM,
        IMMUTABLE
    };

    struct BufferSpec
    {
        UsageHint usageHint;
        std::size_t multiBuffersCount;
    };

    class Buffer
    {
      public:
        Buffer(const UsageHint& usageHint);
        UsageHint getUsageHint() const;
        virtual ~Buffer() = default;

      private:
        UsageHint usageHint;
    };
} // namespace blitz