#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLFloatUniformVariable : public UniformVariable<float>, public OpenGLUniformVariable
    {
      public:
        OpenGLFloatUniformVariable(const GLint& variableLocation, const float& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl