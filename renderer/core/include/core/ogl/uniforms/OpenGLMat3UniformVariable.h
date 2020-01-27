#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <blitzcommon/DataType.h>
#include <mathfu/matrix.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLMat3UniformVariable : public UniformVariable<Matrix3f>, public OpenGLUniformVariable
    {
      public:
        OpenGLMat3UniformVariable(const GLint& variableLocation,
                                     const Matrix3f& value,
                                     const char* const name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl