#include "GL/glew.h"
#include <core/ogl/uniforms/OpenGLMat3UniformVariable.h>
#include <core/DataType.h>

namespace blitz::ogl
{
    OpenGLMat3UniformVariable::OpenGLMat3UniformVariable(const GLint& variableLocation, const Matrix3f& value, const std::string& name)
    : UniformVariable<Matrix3f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }

    void OpenGLMat3UniformVariable::bind()
    {
        glUniformMatrix3fv(variableLocation, 1, GL_FALSE, value.data_->data_);
    }

    DataType OpenGLMat3UniformVariable::getType() const { return DataType::MATRIX3F; }
} // namespace blitz::ogl