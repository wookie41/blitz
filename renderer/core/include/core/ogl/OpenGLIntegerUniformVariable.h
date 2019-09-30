#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>

namespace blitz
{
    class OpenGLIntegerUniformVariable : public UniformVariable<uint32_t>
    {
      public:
        OpenGLIntegerUniformVariable(const GLint& variableLocation,
                                     const uint32_t& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;

    private:
        GLint variableLocation;

    };
} // namespace blitz