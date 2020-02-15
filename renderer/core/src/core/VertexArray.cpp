#include <core/VertexArray.h>

namespace blitz
{
    Buffer* VertexArray::getBoundElementBuffer() const { return elementBuffer; }

    Buffer* VertexArray::getBoundVertexBuffer() const { return vertexBuffer; }

    void VertexArray::addAttribute(const VertexAttributeDef& vertexAttributeDef)
    {
        const auto x = vertexAttributeDef.name.c_str();
        const auto nameHash = hashString(x);
        attributes[nameHash] = vertexAttributeDef;
    }

    const VertexAttributeDef& VertexArray::getAttribute(const hash& nameHash) const
    {
        const auto attribIt = attributes.find(nameHash);
        DCHECK_F(attribIt != attributes.end(), "VAO doesn't have attribute '%d'", nameHash);
        return attribIt->second;
    }

    DataType VertexArray::getIndicesType() const { return indicesType; }

    VertexArray::~VertexArray()
    {
        free(vertexBuffer);
        free(elementBuffer);
    }
} // namespace blitz