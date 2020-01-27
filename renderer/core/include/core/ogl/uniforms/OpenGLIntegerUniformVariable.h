#pragma once

#include <GL/glew.h>
#include <blitzcommon/DataType.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLIntegerUniformVariable : public UniformVariable<int32>, public OpenGLUniformVariable
    {
      public:
        OpenGLIntegerUniformVariable(const GLint& variableLocation, const int32& value, const char* const name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl