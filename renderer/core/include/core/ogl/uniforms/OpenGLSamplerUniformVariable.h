#pragma once

#include <core/Precompiled.h>
#include <core/TextureSpec.h>
#include <core/UniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

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