#include <core/ogl/uniforms/OpenGLMat3UniformVariable.h>

namespace blitz::ogl
{
    OpenGLMat3UniformVariable::OpenGLMat3UniformVariable(const GLint& variableLocation, const Matrix3f& value, const char* const name)
    : UniformVariable<Matrix3f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }

    void OpenGLMat3UniformVariable::bind()
    {
        glUniformMatrix3fv(variableLocation, 1, GL_FALSE, value.data_->data_);
        dirty = false;
    }

    DataType OpenGLMat3UniformVariable::getType() const { return DataType::MATRIX3F; }
} // namespace blitz::ogl