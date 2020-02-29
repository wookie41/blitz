#pragma once

#include <blitzcommon/DataType.h>
#include <core/Range.h>

// TODO
// 1. Consider adding some inner lock, as the Buffer can be shared between several contextes
// The above might not be necessary if RenderCommands are executed properly.

namespace blitz
{
    enum class BufferBindTarget
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
        uint32 size;
        UsageHint usageHint;
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

        virtual void bind(const BufferBindTarget& bindTarget) = 0;

        UsageHint getUsageHint() const;

        uint32 getSizeInBytes() const;

        bool IsReadable() const;

        bool IsWriteable() const;

        void setSize(const uint32& sizeInBytes);

        virtual ~Buffer() = default;

      protected:
        int32 size;
        BindHint bindHint;
        bool isReadable;
        bool isWriteable;
        UsageHint usageHint;
    };
} // namespace blitz