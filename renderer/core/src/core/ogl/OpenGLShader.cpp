#include <core/VertexArray.h>
#include <core/ogl/OpenGLShader.h>
#include <loguru.hpp>

namespace blitz
{
    OpenGLShader::OpenGLShader(GLuint shaderID, const std::unordered_map<hash, IUniformVariable*>& uniforms)
    : Shader(uniforms), shaderID(shaderID)
    {
    }

    void OpenGLShader::use()
    {
        DLOG_F(INFO, "[OpenGL] Using shader %d", shaderID);
        vertexArray->bind();
        glUseProgram(shaderID);
        bindDirtyVariables();
    }
} // namespace blitz
