#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class OpenGLIntegerUniformVariable : public UniformVariable<uint32_t>
    {
      public:
        OpenGLIntegerUniformVariable(const GLint& variableLocation,
                                     const uint32_t& value,
                                     const std::string& name);

        void bind() override;

        UniformVariableType getType() const override;

    private:
        GLint variableLocation;

    };
} // namespace blitz