#include <core/ogl/OpenGLDevice.h>
#include <core/ogl/shader/OpenGLShaderFactory.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>

namespace blitz
{

    OpenGLDevice::OpenGLDevice() { shaderFactory = new OpenGLShaderFactory(); }

    OpenGLDevice::~OpenGLDevice() { delete shaderFactory; }

    Shader* OpenGLDevice::createShader(const ShaderSource& shaderSource) const
    {
        return shaderFactory->createShader(shaderSource);
    }

    Texture *OpenGLDevice::createTexture(const TextureSpec &textureSpec) const
    {
        const auto& textureID = OpenGLTextureCreator::create(textureSpec);
    }
} // namespace blitz