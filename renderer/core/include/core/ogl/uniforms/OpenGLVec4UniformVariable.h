#pragma once

#include <GL/glew.h>
#include <core/DataType.h>
#include <core/Math.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class OpenGLVec4UniformVariable : public UniformVariable<Vector4f>
    {
      public:
        OpenGLVec4UniformVariable(const GLint& variableLocation, const Vector4f& value, const std::string& name);

        void bind() override;

        DataType getType() const override;

      private:
        GLint variableLocation;
    };
} // namespace blitz