#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLMat4UniformVariable : public UniformVariable<Matrix4f>, public OpenGLUniformVariable
    {
      public:
        OpenGLMat4UniformVariable(const GLint& variableLocation, const Matrix4f& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl