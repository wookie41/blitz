#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class Buffer;
    class OpenGLContext;

    struct VertexAttributeDef
    {
        Buffer* buffer;
        char* name;
        DataType dataType;
        uint32 size;
        bool normalize;
        uint32 stride;
        uint64 offset;
        uint32 updateDivisor;
    };

    class VertexArray : NonCopyable
    {
      public:
        explicit VertexArray(uint8 numAttributes);

        void setup();

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void setupAttributes() = 0;

        virtual void bindElementBuffer(Buffer* buffer, const DataType& indicesType) = 0;

        void addAttribute(const VertexAttributeDef& vertexAttributeDef);

        DataType getIndicesType() const;

        virtual ~VertexArray();

        DataType indicesType = DataType::UINT;
        Buffer* elementBuffer = nullptr;

        uint8 attributesCount = 0;
        VertexAttributeDef* attributes = nullptr;
    };

} // namespace blitz