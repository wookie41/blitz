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

        //hashes in the maps are hashes of the names of the attributes/uniforms
        std::unordered_map<hash, IUniformVariable*> extractUniformVariables(GLuint shaderID, const std::unordered_map<hash, UniformBlock*>& uniformBlocks);
        std::unordered_map<hash, UniformBlock*> extractUniformBlocks(GLuint shaderID);
        std::unordered_map<hash, GLuint> createBindingPoints(GLuint shaderID, const std::unordered_map<hash, UniformBlock *>& uniformBlocks);
        std::vector<ShaderOutput> extractShaderOutputs(GLuint shaderID);
        std::unordered_map<hash, GLuint> extractSamplersMapping(GLuint shaderID);
    };
}