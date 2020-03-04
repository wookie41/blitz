#pragma once

#include <core/Precompiled.h>
#include <core/Shader.h>

namespace blitz::ogl
{
    class OpenGLShaderFactory;

    class OpenGLShader : public Shader
    {
        friend OpenGLShaderFactory;

      public:
      
        void use() override;
        void disable() override;

      private:
        OpenGLShader(const blitz::string& name,
                     const GLuint& shaderID,
                     Array<IUniformVariable*>* uniforms,
                     Array<UniformBlock>* uniformBlocks,
                     Array<ShaderOutput>* outputs);

        const GLuint shaderID;
    };
} // namespace blitz::ogl
