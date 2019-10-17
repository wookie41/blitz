#include <GL/glew.h>
#include <core/TextureSampler.h>
#include <core/ogl/uniforms/OpenGLSampler3DUniformVariable.h>

namespace blitz
{
    OpenGLSampler3DUniformVariable::OpenGLSampler3DUniformVariable(const GLint& variableLocation,
                                                                   TextureSampler* value,
                                                                   const std::string& name)
    : UniformVariable<TextureSampler*>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }

    void OpenGLSampler3DUniformVariable::bind() { value->bind(); }

    DataType OpenGLSampler3DUniformVariable::getType() const { return DataType::SAMPLER3D; }
} // namespace blitz