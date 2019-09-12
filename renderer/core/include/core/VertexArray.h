#pragma once

#include <cstdint>
#include <unordered_map>

#include <core/DataType.h>

#include <blitzcommon/NonCopyable.h>
#include <blitzcommon/HashUtils.h>

namespace blitz
{
    struct VertexAttributeDef
    {
        std::string name;
        DataType dataType;
        uint16_t size;
        bool normalize;
        uint32_t stride;
        uint64_t offset;
    };

    class Buffer;

    class VertexArray : NonCopyable
    {
      public:
        VertexArray();

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void bindVertexBuffer(Buffer* buffer) = 0;
        virtual void bindElementBuffer(Buffer* buffer) = 0;

        void addAttribute(const VertexAttributeDef& vertexAttributeDef);

        virtual void bindAttribute(const hash& nameHash) = 0;

        virtual void enable(const hash& nameHash) = 0;
        virtual void disable(const hash& nameHash) = 0;

        Buffer* getBoundVertexBuffer() const;
        Buffer* getBoundElementBuffer() const;

        virtual ~VertexArray() = default;

    protected:

        const VertexAttributeDef& getAttribute(const hash& nameHash) const;

        Buffer* vertexBuffer;
        Buffer* elementBuffer;
        std::unordered_map<hash, VertexAttributeDef> attributes;
    };

} // namespace blitz