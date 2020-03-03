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
        for (uint8 attrIdx = 0; attrIdx < attributesCount; ++attrIdx)
        {
            // TODO this is okay for now, but allowing each VertexAttributeDef
            // to hold it's own name will cause many copies of the same string, so
            // a string pool should be introduced for holding strings like
            // uniform names, vertex attributes names and etc
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