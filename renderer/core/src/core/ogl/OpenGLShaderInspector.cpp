#include <core/ogl/OpenGLShaderInspector.h>
#include <loguru.hpp>

#include <core/ogl/OpenGLIntegerUniformVariable.h>

const GLsizei maxNameLength = 32;

namespace blitz
{

    std::unordered_map<hash, IUniformVariable *> OpenGLShaderInspector::extractUniformVariables(GLuint shaderID)
    {
        std::unordered_map<hash, IUniformVariable *> uniforms;

        GLint numberOfUniforms;

        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

        DLOG_F(INFO, "[OpenGL] Program %d has %d uniforms ", shaderID, numberOfUniforms);

        GLint size;
        GLenum type;
        GLsizei nameLength;
        char* name = new char[maxNameLength];

        for (GLuint uniformIdx = 0; uniformIdx < numberOfUniforms; ++uniformIdx)
        {
            glGetActiveUniform(shaderID, uniformIdx, maxNameLength, &nameLength, &size, &type, name);
            auto variableLocation = glGetUniformLocation(shaderID, name);
            switch (type)
            {
                case GL_INT:
                    uniforms[hashString(name)] = new OpenGLIntegerUniformVariable(variableLocation, 0, name);
                    break;
                default:
                    DLOG_F(ERROR, "[OpenGL] Unsupported uniform variable '%s' type %d", name, type);
            }
        }

        delete[] name;
        return uniforms;
    }
}