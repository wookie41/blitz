#include <core/ogl/uniforms/OpenGLIntegerUniformVariable.h>

namespace blitz::ogl
{
    void OpenGLIntegerUniformVariable::bind()
    {
        glUniform1i(variableLocation, value);
        dirty = false;
    }

    DataType OpenGLIntegerUniformVariable::getType() const { return DataType::INT; }

    OpenGLIntegerUniformVariable::OpenGLIntegerUniformVariable(const GLint& variableLocation, const GLint& value, const blitz::string& name)
    : UniformVariable<GLint>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl