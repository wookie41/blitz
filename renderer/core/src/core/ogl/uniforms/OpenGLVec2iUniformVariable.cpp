#include <core/ogl/uniforms/OpenGLVec2iUniformVariable.h>

namespace blitz::ogl
{
    void OpenGLVec2iUniformVariable::bind()
    {
        glUniform2i(variableLocation, value.x, value.y);
        dirty = false;
    }

    DataType OpenGLVec2iUniformVariable::getType() const { return DataType::VECTOR2I; }

    OpenGLVec2iUniformVariable::OpenGLVec2iUniformVariable(const GLint& variableLocation, const Vector2i& value, const blitz::string& name)
    : UniformVariable<Vector2i>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl