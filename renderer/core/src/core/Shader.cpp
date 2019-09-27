#include <core/Shader.h>

namespace blitz
{
    void Shader::attach(VertexArray* vertexArray)
    {
        this->vertexArray = vertexArray;
    }
} // namespace blitz