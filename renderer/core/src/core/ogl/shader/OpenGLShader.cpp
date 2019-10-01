#include <core/VertexArray.h>
#include <core/ogl/shader/OpenGLShader.h>
#include <loguru.hpp>

namespace blitz
{
    OpenGLShader::OpenGLShader(const std::string& name,
                               GLuint shaderID,
                               const std::unordered_map<hash, IUniformVariable*>& uniforms,
                               const std::unordered_map<hash, UniformBlock*>& unifomBlocks)
    : Shader(name, uniforms, unifomBlocks), shaderID(shaderID)
    {
        GLuint bindingPoint = 0;
        while (bindingPoint++ < GL_MAX_UNIFORM_BUFFER_BINDINGS)
        {
            availableBindingPoints.push_back(bindingPoint);
        }
    }

    void OpenGLShader::use()
    {
        DLOG_F(INFO, "[OpenGL] Using shader %d", shaderID);
        vertexArray->bind();
        glUseProgram(shaderID);
        bindDirtyVariables();
    }

    void OpenGLShader::bindUniformBlock(const std::string& blockName, Buffer* buffer) {}

} // namespace blitz
