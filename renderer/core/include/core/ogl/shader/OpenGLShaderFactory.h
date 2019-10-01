#pragma once

#include <blitzcommon/NonCopyable.h>
#include <core/ShaderSource.h>

namespace blitz
{
    class Shader;
    class OpenGLShaderCompiler;
    class OpenGLShaderInspector;

    class OpenGLShaderFactory :NonCopyable
    {
    public:
        OpenGLShaderFactory();

        Shader* createShader(const ShaderSource& shaderSource);

        ~OpenGLShaderFactory();

    private:
        OpenGLShaderCompiler* compiler;
        OpenGLShaderInspector* inspector;
    };
}