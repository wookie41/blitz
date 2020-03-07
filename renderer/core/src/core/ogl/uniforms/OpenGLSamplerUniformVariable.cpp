#include <core/TextureSampler.h>
#include <core/ogl/uniforms/OpenGLSamplerUniformVariable.h>

namespace blitz::ogl
{
    OpenGLSamplerUniformVariable::OpenGLSamplerUniformVariable(const GLint& variableLocation,
                                                               TextureSampler* sampler,
                                                               const blitz::string& name,
                                                               const GLenum& type)
    : UniformVariable<TextureSampler*>(sampler, name), OpenGLUniformVariable(variableLocation), samplerType(type)
    {
        switch (type)
        {
        case GL_SAMPLER_1D:
            dataType = DataType::SAMPLER1D;
            break;
        case GL_SAMPLER_2D:
            dataType = DataType::SAMPLER2D;
            break;
        case GL_SAMPLER_3D:
            dataType = DataType::SAMPLER3D;
            break;
        default:
            assert(0);
        }
    }

    void OpenGLSamplerUniformVariable::bind()
    {
        if (value == nullptr)
            return;

        value->bind();
        dirty = false;
    }

    DataType OpenGLSamplerUniformVariable::getType() const { return dataType; }
} // namespace blitz::ogl