#include <core/Buffer.h>
#include <core/VertexArray.h>

namespace blitz
{
    VertexArray::VertexArray(uint8 numAttributes) { attributes = new VertexAttributeDef[numAttributes]; }

    void VertexArray::addAttribute(const VertexAttributeDef& vertexAttributeDef)
    {
        attributes[attributesCount++] = vertexAttributeDef;
    }
    DataType VertexArray::getIndicesType() const { return indicesType; }

    VertexArray::~VertexArray()
    {
        delete elementBuffer;
        for (uint8 attrIdx = 0; attrIdx < attributesCount; ++attrIdx)
        {
            // attributes can share the buffer, double delete can happen here!
            delete attributes[attrIdx].buffer;
            delete attributes[attrIdx].name;
        }
        delete[] attributes;
    }

    void VertexArray::setup()
    {
        bind();
        setupAttributes();
    }

} // namespace blitz