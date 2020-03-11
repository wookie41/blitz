#include <core/ogl/uniforms/OpenGLBoolUniformVariable.h>

namespace blitz::ogl
{
    void OpenGLBoolUniformVariable::bind()
    {
        glUniform1i(variableLocation, value);
        dirty = false;
    }

    DataType OpenGLBoolUniformVariable::getType() const { return DataType::BOOL; }

    OpenGLBoolUniformVariable::OpenGLBoolUniformVariable(const GLint& variableLocation, const bool& value, const blitz::string& name)
    : UniformVariable<bool>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }
} // namespace blitz::ogl