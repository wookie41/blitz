#pragma once

#include <GL/glew.h>
#include <core/DataType.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz
{
    class OpenGLMat4UniformVariable : public UniformVariable<Matrix4f>, public OpenGLUniformVariable
    {
      public:
        OpenGLMat4UniformVariable(const GLint& variableLocation, const Matrix4f& value, const std::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz