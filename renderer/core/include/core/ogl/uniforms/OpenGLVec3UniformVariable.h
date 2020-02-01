#pragma once

#include <core/Precompiled.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLVec3UniformVariable: public UniformVariable<Vector3f>, public OpenGLUniformVariable
    {
      public:
        OpenGLVec3UniformVariable(const GLint& variableLocation,
                                     const Vector3f& value,
                                     const char* const name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl