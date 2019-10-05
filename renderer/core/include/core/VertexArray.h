#pragma once

#include <unordered_map>

#include <core/DataType.h>
#include <blitzcommon/HashUtils.h>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class Buffer;
    class OpenGLContext;


    struct VertexAttributeDef
    {
        Buffer* buffer;
        std::string name;
        DataType dataType;
        uint16 size;
        bool normalize;
        uint32 stride;
        uint64 offset;
        uint16 updateDivisor;
    };

    class VertexArray : NonCopyable
    {
      public:
        VertexArray() = default;
        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bindVertexBuffer(Buffer* buffer) = 0;
        virtual void bindElementBuffer(Buffer* buffer) = 0;

        void addAttribute(const VertexAttributeDef& vertexAttributeDef);

        virtual void bindAttribute(const hash& nameHash) = 0;

        virtual void enableAttribute(const hash &nameHash) = 0;
        virtual void disableAttribute(const hash &nameHash) = 0;

        Buffer* getBoundVertexBuffer() const;
        Buffer* getBoundElementBuffer() const;

        virtual ~VertexArray() = default;

      private:

      protected:
        const VertexAttributeDef& getAttribute(const hash& nameHash) const;

        Buffer* vertexBuffer = nullptr;
        Buffer* elementBuffer = nullptr;
        std::unordered_map<hash, VertexAttributeDef> attributes;
    };

} // namespace blitz