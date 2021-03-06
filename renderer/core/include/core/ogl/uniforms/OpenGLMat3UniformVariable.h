#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLMat3UniformVariable : public UniformVariable<Matrix3f>, public OpenGLUniformVariable
    {
      public:
        OpenGLMat3UniformVariable(const GLint& variableLocation, const Matrix3f& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl