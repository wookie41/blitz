#include <core/Shader.h>

namespace blitz
{
    Shader::Shader(const std::unordered_map<hash, IUniformVariable*>& uniforms) :uniformVariables(uniforms) {}

    void Shader::attach(VertexArray* vertexArray) { this->vertexArray = vertexArray; }
} // namespace blitz