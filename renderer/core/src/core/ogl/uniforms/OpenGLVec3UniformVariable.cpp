#include <core/ogl/uniforms/OpenGLVec3UniformVariable.h>

#include "GL/glew.h"
namespace blitz
{
    void OpenGLVec3UniformVariable::bind() { glUniform3f(variableLocation, value.x, value.y, value.z); }

    DataType OpenGLVec3UniformVariable::getType() const { return DataType::VECTOR3F; }

    OpenGLVec3UniformVariable::OpenGLVec3UniformVariable(const GLint& variableLocation, const Vector3f& value, const std::string& name)
    : UniformVariable<Vector3f>(value, name), variableLocation(variableLocation)
    {
    }
} // namespace blitz