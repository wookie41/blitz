#pragma once

#include <cstdint>


//TODO
// 1. Consider adding some inner lock, as the Buffer can be shared between several contextes
// The above might not be necessary if RenderCommands are executed properly.

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

    class Context;

    class Buffer
    {
      public:
        Buffer(const UsageHint& usageHint);

        virtual void bind(const BufferBindTarget& bindTarget) = 0;

        UsageHint getUsageHint() const;

        virtual ~Buffer() = default;

      private:
        UsageHint usageHint;
    };
} // namespace blitz