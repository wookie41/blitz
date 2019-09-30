#include <core/ogl/OpenGLIntegerUniformVariable.h>

#include "GL/glew.h"

namespace blitz
{
    void OpenGLIntegerUniformVariable::bind() { glUniform1i(variableLocation, value); }

    DataType OpenGLIntegerUniformVariable::getType() const { return DataType::INT; }

    OpenGLIntegerUniformVariable::OpenGLIntegerUniformVariable(const GLint& variableLocation,
                                                               const uint32_t& value,
                                                               const std::string& name)
    : UniformVariable<uint32_t>(value, name), variableLocation(variableLocation)
    {
    }
} // namespace blitz