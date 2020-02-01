#pragma once

#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLDoubleUniformVariable : public UniformVariable<double>, public OpenGLUniformVariable
    {
      public:
        OpenGLDoubleUniformVariable(const GLint& variableLocation,
                                     const double& value,
                                     const char* const name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl