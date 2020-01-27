#include <core/Shader.h>
#include <core/UniformBlock.h>
#include <core/VertexArray.h>

namespace blitz
{
    Shader::Shader(const char* const name,
                   const std::unordered_map<hash, IUniformVariable*>& uniforms,
                   const std::unordered_map<hash, UniformBlock*>& uniformBlocks,
                   const std::unordered_map<hash, ShaderOutput*>& outputs)
    : shaderName(name), uniformVariables(uniforms), uniformBlocks(uniformBlocks), shaderOutputs(outputs)
    {
        for (const auto& uniform : uniformVariables)
        {
            const auto sampler = dynamic_cast<UniformVariable<TextureSampler*>*>(uniform.second);
            if (sampler != nullptr)
            {
                samplers.push_back(sampler);
            }
            uniform.second->setWatcher([this](hash h) { this->markAsDirty(h); });
        }
    }

    void Shader::markAsDirty(hash uniformNameHash) { dirtyUniforms.insert(uniformNameHash); }

    void Shader::bindDirtyVariables()
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
        for (const auto& uniformVariable : uniformVariables)
            delete uniformVariable.second;

        for (const auto& uniformBlock : uniformBlocks)
            delete uniformBlock.second;

        for (const auto& output : shaderOutputs)
            delete output.second;
    }

    const std::unordered_map<hash, ShaderOutput*>& Shader::getShaderOutputs() const { return shaderOutputs; }
} // namespace blitz