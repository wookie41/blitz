#pragma once

#include <GL/glew.h>
#include <blitzcommon/HashUtils.h>
#include <blitzcommon/NonCopyable.h>
#include <core/ShaderOutput.h>
#include <unordered_map>

namespace blitz
{
    struct UniformBlock;
    class IUniformVariable;
}

namespace blitz::ogl
{
    class OpenGLShaderInspector : NonCopyable
    {
      public:
        // hashes in the maps are hashes of the names of the attributes/uniforms
        std::unordered_map<hash, IUniformVariable*> extractUniformVariables(GLuint shaderID, const std::unordered_map<hash, UniformBlock*>& uniformBlocks) const;
        std::unordered_map<hash, UniformBlock*> extractUniformBlocks(GLuint shaderID) const;
        std::unordered_map<hash, GLuint> createBindingPoints(GLuint shaderID, const std::unordered_map<hash, UniformBlock*>& uniformBlocks) const;
        std::unordered_map<hash, ShaderOutput*> extractShaderOutputs(GLuint shaderID) const;
    };
} // namespace blitz::ogl