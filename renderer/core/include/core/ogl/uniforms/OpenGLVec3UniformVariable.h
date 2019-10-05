#pragma once

#include <GL/glew.h>
#include <core/UniformVariable.h>
#include <core/DataType.h>

namespace blitz
{
    class OpenGLVec3UniformVariable: public UniformVariable<Vector3f>
    {
      public:
        OpenGLVec3UniformVariable(const GLint& variableLocation,
                                     const Vector3f& value,
                                     const std::string& name);

        void bind() override;

        DataType getType() const override;

    private:
        GLint variableLocation;
    };
} // namespace blitz