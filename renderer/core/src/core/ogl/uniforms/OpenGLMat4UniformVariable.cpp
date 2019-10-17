#include <core/ogl/uniforms/OpenGLMat4UniformVariable.h>

#include "GL/glew.h"
namespace blitz
{
    void OpenGLMat4UniformVariable::bind() { glUniformMatrix4fv(variableLocation, 1, GL_FALSE, value.data_->data_); }

    DataType OpenGLMat4UniformVariable::getType() const { return DataType::INT; }

    OpenGLMat4UniformVariable::OpenGLMat4UniformVariable(const GLint& variableLocation, const Matrix4f& value, const std::string& name)
    : UniformVariable<Matrix4f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz