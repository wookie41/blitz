#include <core/Shader.h>
#include <core/UniformBlock.h>
#include <core/VertexArray.h>

namespace blitz
{
    Shader::Shader(const blitz::string& name,
                   Array<IUniformVariable*>* uniforms,
                   Array<UniformBlock>* uniformBlocks,
                   Array<ShaderOutput>* outputs)
    : shaderName(name), uniformVariables(uniforms), uniformBlocks(uniformBlocks), shaderOutputs(outputs)
    {
    }

    void Shader::markAsDirty(const hash& uniformNameHash) { dirtyUniforms.insert(uniformNameHash); }

    void Shader::setupUniformVariables()
    {
        for (const auto uniformHash : dirtyUniforms)
        {
            uniformVariables[uniformHash]->bind();
        }

        dirtyUniforms.clear();
    }

    void Shader::setOutputTarget(const hash& outputNameHash, Texture* targetTexture)
    {
        const auto& outputIt = shaderOutputs.find(outputNameHash);
        if (outputIt == shaderOutputs.end())
            return;

        outputIt->second->texture = targetTexture;
    }

    Shader::~Shader()
    {
        delete uniformVariables;
        delete uniformBlocks;
        delete shaderOutputs;
    }

    const Array<ShaderOutput>* Shader::getShaderOutputs() const { return shaderOutputs; }
} // namespace blitz