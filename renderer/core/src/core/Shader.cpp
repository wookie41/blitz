#include <core/Shader.h>
#include <core/VertexArray.h>

namespace blitz
{
    Shader::Shader(const std::string& name,
                   const std::unordered_map<hash, IUniformVariable*>& uniforms,
                   const std::unordered_map<hash, UniformBlock*>& uniformBlocks)
    : shaderName(name), uniformVariables(uniforms), uniformBlocks(uniformBlocks)
    {
        for (const auto& uniform : uniformVariables)
        {
            uniform.second->setWatcher([this](hash h) { this->markAsDirty(h); });
        }
    }

    void Shader::attach(VertexArray* array) { this->vertexArray = array; }

    void Shader::markAsDirty(hash uniformNameHash) { dirtyUniforms.insert(uniformNameHash); }

    void Shader::bindDirtyVariables()
    {
        for (const auto uniformHash : dirtyUniforms)
        {
            uniformVariables[uniformHash]->bind();
        }

        dirtyUniforms.clear();
    }
} // namespace blitz