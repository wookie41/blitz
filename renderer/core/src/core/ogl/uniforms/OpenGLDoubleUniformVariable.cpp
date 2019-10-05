#include <core/ogl/uniforms/OpenGLDoubleUniformVariable.h>

#include "GL/glew.h"
namespace blitz
{
    void OpenGLDoubleUniformVariable::bind() { glUniform1d(variableLocation, value); }

    DataType OpenGLDoubleUniformVariable::getType() const { return DataType::INT; }

    OpenGLDoubleUniformVariable::OpenGLDoubleUniformVariable(const GLint& variableLocation, const GLdouble& value, const std::string& name)
    : UniformVariable<GLdouble >(value, name), variableLocation(variableLocation)
    {
    }
} // namespace blitz