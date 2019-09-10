#include <core/VertexArray.h>

namespace blitz
{
    Buffer* VertexArray::getBoundElementBuffer() const { return elementBuffer; }

    Buffer* VertexArray::getBoundVertexBuffer() const { return vertexBuffer; }
} // namespace blitz