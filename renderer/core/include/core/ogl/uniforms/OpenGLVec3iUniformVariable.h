#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLVec3iUniformVariable : public UniformVariable<Vector3i>, public OpenGLUniformVariable
    {
      public:
        OpenGLVec3iUniformVariable(const GLint& variableLocation, const Vector3i& value, const blitz::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl