#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <blitzcommon/DataType.h>
#include <mathfu/vector.h>
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