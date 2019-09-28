#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <blitzcommon/NonCopyable.h>
#include <blitzcommon/HashUtils.h>

namespace blitz
{
    class IUniformVariable;

    class OpenGLShaderInspector :NonCopyable
    {
    public:
        std::unordered_map<hash, IUniformVariable*> extractUniformVariables(GLuint shaderID);
    };
}