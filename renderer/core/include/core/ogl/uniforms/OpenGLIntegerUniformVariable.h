#pragma once

#include <GL/glew.h>
#include <core/DataType.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class OpenGLIntegerUniformVariable : public UniformVariable<GLint>
    {
      public:
        OpenGLIntegerUniformVariable(const GLint& variableLocation, const GLint& value, const std::string& name);

        void bind() override;

        DataType getType() const override;

      private:
        GLint variableLocation;
    };
} // namespace blitz