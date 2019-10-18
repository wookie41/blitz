#pragma once

#include <GL/glew.h>
#include <core/DataType.h>
#include <core/TextureSpec.h>
#include <core/UniformVariable.h>
#include <mathfu/vector.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz
{
    class TextureSampler;
}

namespace blitz::ogl
{
    class OpenGLSampler3DUniformVariable : public UniformVariable<TextureSampler*>, public OpenGLUniformVariable
    {
      public:
        OpenGLSampler3DUniformVariable(const GLint& variableLocation, TextureSampler* value, const std::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl