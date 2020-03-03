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
        Shader(const blitz::string& name, Array<IUniformVariable*>* uniforms, Array<UniformBlock>* uniformBlocks, Array<ShaderOutput>* outputs);

        virtual void use() = 0;
        virtual void disable() = 0;

        virtual void setup(Framebuffer* framebuffer) = 0;

        template <typename T>
        UniformVariable<T>* getUniformVariable(const hash& nameHash);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const char* const name);

        const Array<ShaderOutput>* getShaderOutputs() const;

        virtual void bindUniformBlock(const hash& blockNameHash, const BufferRange* bufferRange) = 0;

        virtual void setOutputTarget(const hash& outputNameHash, Texture* targetTexture);

        virtual ~Shader();

      protected:
        void setupUniformVariables();

        blitz::string shaderName;
        Array<IUniformVariable*>* uniformVariables;
        Array<UniformBlock>* uniformBlocks;
        Array<ShaderOutput>* shaderOutputs;
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
