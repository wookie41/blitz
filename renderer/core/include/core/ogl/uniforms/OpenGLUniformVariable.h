#pragma once

#include <core/Precompiled.h>

namespace blitz::ogl
{
    class OpenGLUniformVariable : NonCopyable
    {
      public:
        explicit OpenGLUniformVariable(const GLint& location);
        const GLint& getVariableLocation();

      protected:
        GLint variableLocation;
    };
} // namespace blitz::ogl