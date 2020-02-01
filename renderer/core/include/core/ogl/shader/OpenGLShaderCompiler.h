#pragma once

#include <core/Precompiled.h>
#include <core/ShaderSource.h>

namespace blitz
{
    class Shader;
}

namespace blitz::ogl
{
    class OpenGLShaderCompiler :NonCopyable
    {
    public:
        GLuint compile(const ShaderSource& shaderSource);
    };
}