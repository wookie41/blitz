#include <core/VertexArray.h>
#include <loguru.hpp>
#include <blitzcommon/HashUtils.h>

namespace blitz
{
    Buffer* VertexArray::getBoundElementBuffer() const { return elementBuffer; }

    Buffer* VertexArray::getBoundVertexBuffer() const { return vertexBuffer; }

    void VertexArray::addAttribute(const VertexAttributeDef &vertexAttributeDef)
    {
        const auto nameHash = hashString(vertexAttributeDef.name);
        attributes[nameHash] = vertexAttributeDef;
        bindAttribute(nameHash);
    }

    const VertexAttributeDef& VertexArray::getAttribute(const hash& nameHash) const
    {
        const auto attribIt = attributes.find(nameHash);
        DCHECK_F(attribIt != attributes.end(), "VAO doesn't have attribute '%ld'", nameHash);
        return attribIt->second;
    }
} // namespace blitz