#include <core/ogl/uniforms/OpenGLVec2UniformVariable.h>

namespace blitz::ogl
{
    void OpenGLVec2UniformVariable::bind()
    {
        glUniform2f(variableLocation, value.x, value.y);
        dirty = false;
    }

    DataType OpenGLVec2UniformVariable::getType() const { return DataType::VECTOR2F; }

    OpenGLVec2UniformVariable::OpenGLVec2UniformVariable(const GLint& variableLocation, const Vector2f& value, const blitz::string& name)
    : UniformVariable<Vector2f>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl