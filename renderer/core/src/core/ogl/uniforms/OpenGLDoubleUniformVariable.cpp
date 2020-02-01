#include <core/ogl/uniforms/OpenGLDoubleUniformVariable.h>

namespace blitz::ogl
{
    void OpenGLDoubleUniformVariable::bind()
    {
        glUniform1d(variableLocation, value);
        dirty = false;
    }

    DataType OpenGLDoubleUniformVariable::getType() const { return DataType::INT; }

    OpenGLDoubleUniformVariable::OpenGLDoubleUniformVariable(const GLint& variableLocation, const GLdouble& value, const char* const name)
    : UniformVariable<GLdouble>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl