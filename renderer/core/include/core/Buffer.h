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
        WRITE,
        UNIFORM_BLOCK
    };


    struct BufferBindingSpec
    {
        size_t offset = 0;
        size_t size;
        uint16 index;
        BufferBindTarget bindTarget;
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
        size_t size;
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

        virtual void bind(const BufferBindingSpec& bindingSpec) = 0;

        UsageHint getUsageHint() const;

        size_t getSizeInBytes() const;

        bool IsReadable() const;

        bool IsWriteable() const;

        void setSize(const size_t& sizeInBytes);

        virtual ~Buffer() = default;

      protected:
        size_t size;
        BindHint bindHint;
        bool isReadable;
        bool isWriteable;
        UsageHint usageHint;
    };
} // namespace blitz