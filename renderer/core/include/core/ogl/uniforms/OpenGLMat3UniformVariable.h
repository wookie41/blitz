#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>
#include <mathfu/matrix.h>

namespace blitz
{
    class OpenGLMat3UniformVariable : public UniformVariable<Matrix3f>
    {
      public:
        OpenGLMat3UniformVariable(const GLint& variableLocation,
                                     const Matrix3f& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;

    private:
        GLint variableLocation;

    };
} // namespace blitz