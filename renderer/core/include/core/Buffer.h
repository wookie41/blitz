#pragma once

#include <cstdint>
#include <core/Range.h>


//TODO
// 1. Consider adding some inner lock, as the Buffer can be shared between several contextes
// The above might not be necessary if RenderCommands are executed properly.

namespace blitz
{
    enum class BindTarget
    {
        VERTEX,
        ELEMENT,
        WRITE
    };

    enum class IndexedBindTarget
    {
        UNIFORM_BLOCK
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
        explicit Buffer(const UsageHint& usageHint);

        virtual void bind(const BindTarget& bindTarget) = 0;
        virtual void bindRange(const BindTarget& bindTarget, const Range& range) = 0;

        virtual void bindIndexed(const IndexedBindTarget& bindTarget, uint16_t index) = 0;
        virtual void bindIndexedRange(const IndexedBindTarget& bindTarget, uint16_t index, const Range& range) = 0;

        UsageHint getUsageHint() const;

        virtual ~Buffer() = default;

      private:
        UsageHint usageHint;
    };
} // namespace blitz