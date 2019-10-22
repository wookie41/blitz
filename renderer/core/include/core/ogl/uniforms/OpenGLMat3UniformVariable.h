#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>
#include <mathfu/matrix.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    class OpenGLMat3UniformVariable : public UniformVariable<Matrix3f>, public OpenGLUniformVariable
    {
      public:
        OpenGLMat3UniformVariable(const GLint& variableLocation,
                                     const Matrix3f& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl