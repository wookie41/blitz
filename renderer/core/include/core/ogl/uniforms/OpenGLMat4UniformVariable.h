#pragma once

#include <GL/glew.h>
#include <core/DataType.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class OpenGLMat4UniformVariable : public UniformVariable<Matrix4f>
    {
      public:
        OpenGLMat4UniformVariable(const GLint& variableLocation, const Matrix4f& value, const std::string& name);

        void bind() override;

        DataType getType() const override;

      private:
        GLint variableLocation;
    };
} // namespace blitz