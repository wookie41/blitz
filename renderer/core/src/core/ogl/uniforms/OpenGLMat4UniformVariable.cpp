#include <core/ogl/uniforms/OpenGLMat4UniformVariable.h>

namespace blitz::ogl
{
    void OpenGLMat4UniformVariable::bind()
    {
        glUniformMatrix4fv(variableLocation, 1, GL_FALSE, value.data_->data_);
        dirty = false;
    }

    DataType OpenGLMat4UniformVariable::getType() const { return DataType::MATRIX4F; }

    OpenGLMat4UniformVariable::OpenGLMat4UniformVariable(const GLint& variableLocation, const Matrix4f& value, const blitz::string& name)
    : UniformVariable<Matrix4f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl