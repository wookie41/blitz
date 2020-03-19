#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLVec2UniformVariable : public UniformVariable<Vector2f>, public OpenGLUniformVariable
    {
      public:
        OpenGLVec2UniformVariable(const GLint& variableLocation, const Vector2f& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl