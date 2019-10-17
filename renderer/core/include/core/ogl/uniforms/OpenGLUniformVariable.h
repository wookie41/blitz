#pragma once

#include <GL/glew.h>
#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class OpenGLUniformVariable : NonCopyable
    {
      public:
        explicit OpenGLUniformVariable(const GLint& location);
        const GLint& getVariableLocation();

      protected:
        GLint variableLocation;
    };
} // namespace blitz