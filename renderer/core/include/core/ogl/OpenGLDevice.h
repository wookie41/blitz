#pragma once

#include <core/Device.h>

namespace blitz
{
    class OpenGLShaderFactory;

    class OpenGLDevice : public Device
    {
      public:
        OpenGLDevice();

        Shader* createShader(const ShaderSource& shaderSource) const override;

        virtual ~OpenGLDevice();

      private:
        OpenGLShaderFactory* shaderFactory;
    };
} // namespace blitz