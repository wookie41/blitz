#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <blitzcommon/DataType.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLFloatUniformVariable : public UniformVariable<float>, public OpenGLUniformVariable
    {
      public:
        OpenGLFloatUniformVariable(const GLint& variableLocation,
                                     const float& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl