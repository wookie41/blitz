#pragma once

#include <GL/glew.h>
#include <blitzcommon/NonCopyable.h>
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