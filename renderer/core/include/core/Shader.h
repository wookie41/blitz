#pragma once

#include <core/Precompiled.h>
#include <core/RendererErrorCode.h>
#include <core/ShaderOutput.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class Buffer;
    class Framebuffer;
    class TextureSampler;
    class VertexArray;

	struct UniformBlock;
    struct BufferRange;

    class Shader : public NonCopyable
    {
      public:
        explicit Shader(const char* shaderName,
                        const std::unordered_map<hash, IUniformVariable*>& uniforms,
                        const std::unordered_map<hash, UniformBlock*>& uniformBlocks,
                        const std::unordered_map<hash, ShaderOutput*>& outputs);

        virtual void use() = 0;
        virtual void disable() = 0;

        virtual void setup(Framebuffer* framebuffer) = 0;

        template <typename T>
        UniformVariable<T>* getUniformVariable(const hash& nameHash);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const char* const name);

        virtual const std::unordered_map<hash, ShaderOutput*>& getShaderOutputs() const;

        virtual void bindUniformBlock(const hash& blockNameHash, const BufferRange* bufferRange) = 0;

        virtual void setOutputTarget(const hash& outputNameHash, Texture* targetTexture);

        void bindDirtyVariables();

        virtual ~Shader();

      protected:
        void markAsDirty(const hash& uniformNameHash);

        const char* const shaderName;
        std::unordered_map<hash, IUniformVariable*> uniformVariables;
        std::unordered_set<hash> dirtyUniforms;
        std::unordered_map<hash, UniformBlock*> uniformBlocks;
        std::unordered_map<hash, ShaderOutput*> shaderOutputs;
        std::vector<IUniformVariable*> samplers;
    };

    template <typename T>
    UniformVariable<T>* Shader::getUniformVariable(const hash& nameHash)
    {
        const auto variableIt = uniformVariables.find(nameHash);
        if (variableIt == uniformVariables.end())
        {
            DLOG_F(ERROR, "Shader '%s' doesn't have uniform with hash %lld", shaderName, nameHash);
            return nullptr;
        }

        auto uniformVariable = variableIt->second;
        return dynamic_cast<UniformVariable<T>*>(uniformVariable);
    }

    template <typename T>
    UniformVariable<T>* Shader::getUniformVariable(const char* const name)
    {
        return getUniformVariable<T>(hashString(name));
    }
} // namespace blitz
