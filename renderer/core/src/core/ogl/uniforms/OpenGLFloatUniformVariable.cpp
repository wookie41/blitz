#include <core/ogl/uniforms/OpenGLFloatUniformVariable.h>

#include "GL/glew.h"
namespace blitz
{
    void OpenGLFloatUniformVariable ::bind() { glUniform1f(variableLocation, value); }

    DataType OpenGLFloatUniformVariable ::getType() const { return DataType::INT; }

    OpenGLFloatUniformVariable ::OpenGLFloatUniformVariable(const GLint& variableLocation, const GLfloat& value, const std::string& name)
    : UniformVariable<GLfloat>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz