#include <core/ogl/uniforms/OpenGLVec4UniformVariable.h>

namespace blitz::ogl
{
    void OpenGLVec4UniformVariable::bind()
    {
        glUniform4f(variableLocation, value.x, value.y, value.z, value.w);
        dirty = false;
    }

    DataType OpenGLVec4UniformVariable::getType() const { return DataType::VECTOR4F; }

    OpenGLVec4UniformVariable::OpenGLVec4UniformVariable(const GLint& variableLocation, const Vector4f& value, const char* const name)
    : UniformVariable<Vector4f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl