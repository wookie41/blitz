#include <core/ogl/uniforms/OpenGLSampler1DUniformVariable.h>
#include <core/TextureSampler.h>
#include <GL/glew.h>

namespace blitz::ogl
{
    OpenGLSampler1DUniformVariable::OpenGLSampler1DUniformVariable(const GLint& variableLocation,
                                                               TextureSampler* value,
                                                               const std::string& name)
    : UniformVariable<TextureSampler*>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }

    void OpenGLSampler1DUniformVariable::bind() { value->bind(); }

    DataType OpenGLSampler1DUniformVariable::getType() const { return DataType::SAMPLER1D; }
} // namespace blitz::ogl