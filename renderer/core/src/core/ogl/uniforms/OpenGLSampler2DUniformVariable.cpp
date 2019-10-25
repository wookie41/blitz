#include <GL/glew.h>
#include <core/TextureSampler.h>
#include <core/ogl/uniforms/OpenGLSampler2DUniformVariable.h>

namespace blitz::ogl
{
    OpenGLSampler2DUniformVariable::OpenGLSampler2DUniformVariable(const GLint& variableLocation,
                                                                   TextureSampler* value,
                                                                   const std::string& name)
    : UniformVariable<TextureSampler*>(value, name), OpenGLUniformVariable(variableLocation)
    {
    }

    void OpenGLSampler2DUniformVariable::bind()
    {
        dirty = false;
        if (value == nullptr)
            return;

        value->bind();
    }

    DataType OpenGLSampler2DUniformVariable::getType() const { return DataType::SAMPLER2D; }
} // namespace blitz::ogl