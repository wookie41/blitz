#include <core/ogl/uniforms/OpenGLVec4UniformVariable.h>

#include "GL/glew.h"
namespace blitz::ogl
{
    void OpenGLVec4UniformVariable::bind() { glUniform4f(variableLocation, value.x, value.y, value.z, value.w); }

    DataType OpenGLVec4UniformVariable::getType() const { return DataType::VECTOR4F; }

    OpenGLVec4UniformVariable::OpenGLVec4UniformVariable(const GLint& variableLocation, const Vector4f& value, const std::string& name)
    : UniformVariable<Vector4f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl