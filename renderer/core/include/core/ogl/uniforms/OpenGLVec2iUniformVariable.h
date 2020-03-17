#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLVec2iUniformVariable : public UniformVariable<Vector2i>, public OpenGLUniformVariable
    {
      public:
        OpenGLVec2iUniformVariable(const GLint& variableLocation, const Vector2i& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl