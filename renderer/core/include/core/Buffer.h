#pragma once

#include <core/Range.h>
#include <cstdint>


// TODO
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

    enum class BindHint
    {
        INDEX,
        VERTEX,
        UNIFORM
    };

    struct BufferSpec
    {
        std::uint32_t size;
        UsageHint usageHint;
        std::size_t multiBuffersCount;
        BindHint bindHint;
        void* initialData;
        bool readable;
        bool writeable;
    };

    class Context;

    class Buffer
    {
      public:
        explicit Buffer(const UsageHint& usageHint);

        virtual void bind(const BindTarget& bindTarget) = 0;

        virtual void bindIndexed(const IndexedBindTarget& bindTarget, uint16_t index) = 0;
        virtual void bindIndexedRange(const IndexedBindTarget& bindTarget, uint16_t index, const Range& range) = 0;

        UsageHint getUsageHint() const;


        uint32_t getSize() const;

        bool IsReadable() const;

        bool IsWriteable() const;

        void setSize(const uint32_t& size);

        virtual ~Buffer() = default;

      protected:
        std::uint32_t size;
        BindHint bindHint;
        bool isReadable, bool isWriteable;
        UsageHint usageHint;
    };
} // namespace blitz