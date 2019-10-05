#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>

namespace blitz
{
    class OpenGLFloatUniformVariable : public UniformVariable<float>
    {
      public:
        OpenGLFloatUniformVariable(const GLint& variableLocation,
                                     const float& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;

    private:
        GLint variableLocation;

    };
} // namespace blitz