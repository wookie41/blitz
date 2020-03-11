#include <core/ogl/uniforms/OpenGLVec3UniformVariable.h>

namespace blitz::ogl
{
    void OpenGLVec3UniformVariable::bind()
    {
        glUniform3f(variableLocation, value.x, value.y, value.z);
        dirty = false;
    }

    DataType OpenGLVec3UniformVariable::getType() const { return DataType::VECTOR3F; }

    OpenGLVec3UniformVariable::OpenGLVec3UniformVariable(const GLint& variableLocation, const Vector3f& value, const blitz::string& name)
    : UniformVariable<Vector3f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl