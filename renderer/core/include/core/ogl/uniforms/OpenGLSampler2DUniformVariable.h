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

    class OpenGLSampler2DUniformVariable : public UniformVariable<TextureSampler*>, public OpenGLUniformVariable
    {
      public:
        OpenGLSampler2DUniformVariable(const GLint& variableLocation, TextureSampler* value, const std::string& name);

        void bind() override;

        DataType getType() const override;
    };
} // namespace blitz::ogl