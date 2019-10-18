#include <core/ogl/OpenGLDevice.h>
#include <core/ogl/shader/OpenGLShaderFactory.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/texture/OpenGLSyncReadTexture.h>
#include <core/ogl/texture/OpenGLSyncWriteTexture.h>
#include <core/ogl/texture/OpenGLSyncReadWriteTexture.h>

namespace blitz::ogl
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

        if (textureSpec.isReadable && !textureSpec.isWriteable)
        {
            return new OpenGLSyncReadTexture(textureID, textureSpec);
        }

        if (!textureSpec.isReadable && textureSpec.isWriteable)
        {
            return new OpenGLSyncWriteTexture(textureID, textureSpec);
        }

        return new OpenGLSyncReadWriteTexture(textureID, textureSpec);
    }
} // namespace blitz::ogl