#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLBoolUniformVariable : public UniformVariable<bool>, public OpenGLUniformVariable
    {
      public:
        OpenGLBoolUniformVariable(const GLint& variableLocation, const bool& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl