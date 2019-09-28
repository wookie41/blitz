#pragma once

#include <unordered_map>
#include <unordered_set>

#include <blitzcommon/NonCopyable.h>
#include <core/UniformVariable.h>
#include <core/RendererErrorCode.h>
class VertexArray;

namespace blitz
{
    class Shader : NonCopyable
    {
      public:
        virtual void use() = 0;

        void attach(VertexArray* vertexArray);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const hash& nameHash);

        template <typename T>
        UniformVariable<T>* getUniformVariable(const std::string& name);

      protected:
        void markUniformAsDirty(const hash& nameHash);
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

    void Shader::markUniformAsDirty(const hash &nameHash)
    {
        dirtyUniforms.insert(nameHash);
    }

    void Shader::bindDirtyVariables()
    {
        for (const auto uniformHash : dirtyUniforms)
        {
            uniformVariables[uniformHash]->bind();
        }

        dirtyUniforms.clear();
    }
} // namespace blitz
