#pragma once

#include <loguru.hpp>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <blitzcommon/NonCopyable.h>
#include <core/RendererErrorCode.h>
#include <core/ShaderOutput.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class Buffer;
    class UniformBlock;
    class VertexArray;
    class BufferRange;

    class Shader : NonCopyable
    {
      public:
        explicit Shader(const std::string& name,
                        const std::unordered_map<hash, IUniformVariable*>& uniforms,
                        const std::unordered_map<hash, UniformBlock*>& uniformBlocks,
                        const std::vector<ShaderOutput>& outputs);

        virtual void use() = 0;

        void attach(VertexArray* array);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const hash& nameHash);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const std::string& name);

        const std::vector<ShaderOutput>& getShaderOutputs() const;

        virtual void bindUniformBlock(const std::string& blockName, const BufferRange* bufferRange) = 0;

        virtual ~Shader() = default;

      protected:
        void markAsDirty(hash uniformNameHash);
        void bindDirtyVariables();

        VertexArray* vertexArray = nullptr;

        std::string shaderName;
        std::unordered_map<hash, IUniformVariable*> uniformVariables;
        std::unordered_set<hash> dirtyUniforms;
        std::unordered_map<hash, UniformBlock*> uniformBlocks;
        std::vector<ShaderOutput> shaderOutputs;
    };

    template <typename T>
    UniformVariable<T>* Shader::getUniformVariable(const hash& nameHash)
    {
        const auto variableIt = uniformVariables.find(nameHash);
        if (variableIt == uniformVariables.end())
        {
            DLOG_F(ERROR, "Shader '%s' doesn't have uniform with hash %lld", shaderName.c_str(), nameHash);
            return nullptr;
        }

        auto uniformVariable = variableIt->second;
        return dynamic_cast<UniformVariable<T>*>(uniformVariable);
    }

    template <typename T>
    UniformVariable<T>* Shader::getUniformVariable(const std::string& name)
    {
        return getUniformVariable<T>(hashString(name));
    }
} // namespace blitz
