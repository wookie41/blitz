#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>
#include <mathfu/vector.h>

namespace blitz
{
    class OpenGLDoubleUniformVariable : public UniformVariable<GLdouble>
    {
      public:
        OpenGLDoubleUniformVariable(const GLint& variableLocation,
                                     const GLdouble& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;

    private:
        GLint variableLocation;

    };
} // namespace blitz