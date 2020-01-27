#pragma once

#include <GL/glew.h>
#include <blitzcommon/DataType.h>
#include <core/TextureSpec.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>
#include <mathfu/vector.h>

namespace blitz
{
    class TextureSampler;
}

namespace blitz::ogl
{
    class OpenGLSamplerUniformVariable : public UniformVariable<TextureSampler*>, public OpenGLUniformVariable
    {
      public:
        OpenGLSamplerUniformVariable(const GLint& variableLocation, TextureSampler* sampler, const char* const name, const GLenum& type);

        void bind() override;

        DataType getType() const override;

      private:
        DataType dataType;
        GLenum samplerType;
    };
} // namespace blitz::ogl