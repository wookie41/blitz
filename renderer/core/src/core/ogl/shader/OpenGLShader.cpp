#include <core/UniformBlock.h>
#include <core/VertexArray.h>
#include <core/ogl/shader/OpenGLShader.h>
#include <loguru.hpp>

namespace blitz
{
    OpenGLShader::OpenGLShader(const std::string& name,
                               GLuint shaderID,
                               const std::unordered_map<hash, IUniformVariable*>& uniforms,
                               const std::unordered_map<hash, UniformBlock*>& unifomBlocks,
                               const std::unordered_map<hash, GLuint>& uniformBlockBindings)
    : Shader(name, uniforms, unifomBlocks), shaderID(shaderID), uniformBlockBindings(uniformBlockBindings)
    {
    }

    void OpenGLShader::use()
    {
        DLOG_F(INFO, "[OpenGL] Using shader %d", shaderID);
        vertexArray->bind();
        glUseProgram(shaderID);
        bindDirtyVariables();
    }

    void OpenGLShader::bindUniformBlock(const std::string& blockName, Buffer* buffer)
    {
    }
} // namespace blitz
