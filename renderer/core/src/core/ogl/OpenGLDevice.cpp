#include <core/ogl/OpenGLDevice.h>
#include <core/ogl/shader/OpenGLShaderFactory.h>

namespace blitz
{

    OpenGLDevice::OpenGLDevice() { shaderFactory = new OpenGLShaderFactory(); }

    OpenGLDevice::~OpenGLDevice() { delete shaderFactory; }

    Shader* OpenGLDevice::createShader(const ShaderSource& shaderSource) const
    {
        return shaderFactory->createShader(shaderSource);
    }
} // namespace blitz