#include <core/ogl/OpenGLIntegerUniformVariable.h>

#include "GL/glew.h"

namespace blitz
{
    void OpenGLIntegerUniformVariable::bind() { glUniform1i(variableLocation, value); }

    UniformVariableType OpenGLIntegerUniformVariable::getType() const { return UniformVariableType::INTEGER; }

    OpenGLIntegerUniformVariable::OpenGLIntegerUniformVariable(const GLint& variableLocation,
                                                               const uint32_t& value,
                                                               const hash& nameHash,
                                                               const std::string& name,
                                                               const UniformVariableWatcher& watcher)
    : UniformVariable<uint32_t>(value, name, watcher), variableLocation(variableLocation)
    {
    }
} // namespace blitz