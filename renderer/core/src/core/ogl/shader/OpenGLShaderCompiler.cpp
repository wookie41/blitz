#include <core/ogl/shader/OpenGLShaderCompiler.h>

namespace blitz::ogl
{
    static char infoLog[1024];

    void checkCompileErrors(unsigned int shader, char* type)
    {
        int success;
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                DLOG_F(ERROR, "[OpenGL] Failed to compile shader of type '%s': %s", type, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                DLOG_F(ERROR, "[OpenGL] Failed to link shader program %s", infoLog);
            }
        }
    }

    void compileShader(GLuint shaderProgramID, GLuint shaderID, const char* shaderSource, char* type)
    {
        glShaderSource(shaderID, 1, &shaderSource,  NULL);
        glCompileShader(shaderID);
#ifndef NDEBUG
        checkCompileErrors(shaderID, type);
#endif
        glAttachShader(shaderProgramID, shaderID);
    }

    GLuint OpenGLShaderCompiler::compile(const ShaderSource& shaderSource)
    {
        GLuint shaderProgramID = glCreateProgram();
        GLuint vertexShader = 0, geometryShader = 0, fragmentShader = 0;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        compileShader(shaderProgramID, vertexShader, shaderSource.vertexShaderSource, "VERTEX");
        compileShader(shaderProgramID, fragmentShader, shaderSource.fragmentShaderSource, "FRAGMENT");

        if (shaderSource.geometryShaderSource != nullptr)
        {
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            compileShader(shaderProgramID, geometryShader, shaderSource.geometryShaderSource, "GEOMETRY");
        }

        glLinkProgram(shaderProgramID);
#ifndef NDEBUG

        checkCompileErrors(shaderProgramID, "PROGRAM");
#endif

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        if (geometryShader != 0)
        {
            glDeleteShader(geometryShader);
        }

        return shaderProgramID;
    }
} // namespace blitz::ogl