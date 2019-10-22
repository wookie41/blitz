#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>
#include <mathfu/vector.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLDoubleUniformVariable : public UniformVariable<double>, public OpenGLUniformVariable
    {
      public:
        OpenGLDoubleUniformVariable(const GLint& variableLocation,
                                     const double& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl