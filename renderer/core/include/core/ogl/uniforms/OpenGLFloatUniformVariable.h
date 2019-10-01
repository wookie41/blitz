#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>

namespace blitz
{
    class OpenGLFloatUniformVariable : public UniformVariable<GLfloat>
    {
      public:
        OpenGLFloatUniformVariable(const GLint& variableLocation,
                                     const GLfloat& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;

    private:
        GLint variableLocation;

    };
} // namespace blitz