#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    OpenGLUniformVariable::OpenGLUniformVariable(const GLint& location) : variableLocation(location) {}
    const GLint& OpenGLUniformVariable::getVariableLocation() { return variableLocation; }
} // namespace blitz::ogl