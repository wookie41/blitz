#include <core/ogl/uniforms/OpenGLIntegerUniformVariable.h>

#include "GL/glew.h"
namespace blitz
{
    void OpenGLIntegerUniformVariable::bind() { glUniform1i(variableLocation, value); }

    DataType OpenGLIntegerUniformVariable::getType() const { return DataType::INT; }

    OpenGLIntegerUniformVariable::OpenGLIntegerUniformVariable(const GLint& variableLocation, const GLint& value, const std::string& name)
    : UniformVariable<GLint>(value, name), variableLocation(variableLocation)
    {
    }
} // namespace blitz