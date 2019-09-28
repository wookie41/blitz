#pragma once

#include <unordered_map>
#include <unordered_set>

#include <blitzcommon/NonCopyable.h>
#include <core/RendererErrorCode.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class VertexArray;

    class Shader : NonCopyable
    {
      public:
        explicit Shader(const std::unordered_map<hash, IUniformVariable*>& uniforms);

        virtual void use() = 0;

        void attach(VertexArray* array);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const hash& nameHash);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const std::string& name);

        virtual ~Shader() = default;

      protected:
        void markAsDirty(hash uniformNameHash);
        void bindDirtyVariables();

        VertexArray* vertexArray;

        std::unordered_map<hash, IUniformVariable*> uniformVariables;
        std::unordered_set<hash> dirtyUniforms;
    };

    template <typename T>
    UniformVariable<T>* Shader::getUniformVariable(const hash& nameHash)
    {
        const auto variableIt = uniformVariables.find(nameHash);
        if (variableIt == uniformVariables.end())
        {
            exit(RendererErrorCode::UNKNOWN_SHADER_UNIFORM_VARIABLE);
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
