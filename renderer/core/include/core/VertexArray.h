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

        bool isDirty;
        bool shouldCheckDirty;
    };

    class Buffer;

    class VertexArray : NonCopyable
    {
      public:
        VertexArray() = default;

        virtual void bindVertexBuffer(Buffer* buffer) = 0;
        virtual void bindElementBuffer(Buffer* buffer) = 0;
        virtual void setVertexAttribute(const VertexAttributeDef& vertexAttributeDef) = 0;

        Buffer* getBoundVertexBuffer() const;
        Buffer* getBoundElementBuffer() const;

        virtual ~VertexArray() = default;

      private:
        Buffer* vertexBuffer;
        Buffer* elementBuffer;
    };

} // namespace blitz