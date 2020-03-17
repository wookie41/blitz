#include <core/ogl/uniforms/OpenGLVec3iUniformVariable.h>

namespace blitz::ogl
{
    void OpenGLVec3iUniformVariable::bind()
    {
        glUniform3i(variableLocation, value.x, value.y, value.z);
        dirty = false;
    }

    DataType OpenGLVec3iUniformVariable::getType() const { return DataType::VECTOR3I; }

    OpenGLVec3iUniformVariable::OpenGLVec3iUniformVariable(const GLint& variableLocation, const Vector3i& value, const blitz::string& name)
    : UniformVariable<Vector3i>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl