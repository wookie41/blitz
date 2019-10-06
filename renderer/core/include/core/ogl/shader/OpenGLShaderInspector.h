#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <blitzcommon/NonCopyable.h>
#include <blitzcommon/HashUtils.h>
#include <core/ShaderOutput.h>

namespace blitz
{
    class UniformBlock;
    class IUniformVariable;

    class OpenGLShaderInspector :NonCopyable
    {
    public:
        std::unordered_map<hash, IUniformVariable*> extractUniformVariables(GLuint shaderID, const std::unordered_map<hash, UniformBlock*>& uniformBlocks);
        std::unordered_map<hash, UniformBlock*> extractUniformBlocks(GLuint shaderID);
        std::unordered_map<hash, GLuint> createBindingPoints(GLuint shaderID, const std::unordered_map<hash, UniformBlock *>& uniformBlocks);
        std::vector<ShaderOutput> extractShaderOutputs(GLuint shaderID);
    };
}