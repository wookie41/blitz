#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLVec4UniformVariable : public UniformVariable<Vector4f>, public OpenGLUniformVariable
    {
      public:
        OpenGLVec4UniformVariable(const GLint& variableLocation, const Vector4f& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl