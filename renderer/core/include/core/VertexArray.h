#pragma once

#include <blitzcommon/NonCopyable.h>
#include <core/DataType.h>
#include <cstdint>

namespace blitz
{
    struct VertexAttributeDef
    {
        uint16_t index;
        char* name;
        DataType dataType;
        uint16_t size;
        bool normalize;
        uint64_t stride;
        uint64_t offset;
    };

    class Buffer;

    class VertexArray : NonCopyable
    {
      public:
        VertexArray() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bindVertexBuffer(Buffer* buffer) = 0;
        virtual void bindElementBuffer(Buffer* buffer) = 0;
        virtual void setVertexAttribute(const VertexAttributeDef& vertexAttributeDef) = 0;

        Buffer* getBoundVertexBuffer() const;
        Buffer* getBoundElementBuffer() const;

        virtual ~VertexArray() = default;

    protected:
        Buffer* vertexBuffer;
        Buffer* elementBuffer;
    };

} // namespace blitz