#pragma once

#include <core/Device.h>

namespace blitz::ogl
{
    class OpenGLShaderFactory;

    class OpenGLDevice : public Device
    {
      public:
        OpenGLDevice();

        Shader* createShader(const ShaderSource& shaderSource) const override;

        Texture *createTexture(const TextureSpec &textureSpec) const override;

        virtual ~OpenGLDevice();

      private:
        OpenGLShaderFactory* shaderFactory;
    };
} // namespace blitz::ogl