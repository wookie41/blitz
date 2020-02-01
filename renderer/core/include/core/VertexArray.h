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
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bindElementBuffer(Buffer* buffer, const DataType& indicesType) = 0;

        void addAttribute(const VertexAttributeDef& vertexAttributeDef);

        virtual void bindAttribute(Shader* shader, const hash& nameHash) = 0;

        virtual void enableAttribute(Shader* shader, const hash &nameHash) = 0;
        virtual void disableAttribute(Shader* shader, const hash &nameHash) = 0;

        Buffer* getBoundVertexBuffer() const;

        DataType getIndicesType() const;

        Buffer* getBoundElementBuffer() const;

        virtual ~VertexArray() = default;

      private:

      protected:
        const VertexAttributeDef& getAttribute(const hash& nameHash) const;

        Buffer* vertexBuffer = nullptr;

        DataType indicesType = DataType::UINT;
        Buffer* elementBuffer = nullptr;

        std::unordered_map<hash, VertexAttributeDef> attributes;
    };

} // namespace blitz