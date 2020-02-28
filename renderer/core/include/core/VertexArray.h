#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class Buffer;
    class OpenGLContext;

    struct VertexAttributeDef
    {
        Buffer* buffer;
        std::string name;
        DataType dataType;
        uint32 size;
        bool normalize;
        uint32 stride;
        uint64 offset;
        uint32 updateDivisor;
    };

    class Shader;

    class VertexArray : NonCopyable
    {
      public:
        VertexArray() = default;

        void setup();
        void detach();

        virtual void bindElementBuffer(Buffer* buffer, const DataType& indicesType) = 0;

        void addAttribute(const VertexAttributeDef& vertexAttributeDef);

        Buffer* getBoundVertexBuffer() const;

        DataType getIndicesType() const;

        Buffer* getBoundElementBuffer() const;

        virtual ~VertexArray();

      protected:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bindAttribute(const hash& nameHash) = 0;
        virtual void enableAttribute(const hash& nameHash) = 0;
        virtual void disableAttribute(const hash& nameHash) = 0;

        const VertexAttributeDef& getAttribute(const hash& nameHash) const;

        Buffer* vertexBuffer = nullptr;

        DataType indicesType = DataType::UINT;
        Buffer* elementBuffer = nullptr;

      private:
        std::unordered_map<hash, VertexAttributeDef> attributes;
    };

} // namespace blitz