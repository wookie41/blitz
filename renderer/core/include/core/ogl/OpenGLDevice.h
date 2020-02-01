#pragma once

#include <core/Precompiled.h>
#include <core/Device.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>

namespace blitz::ogl
{
    class OpenGLShaderFactory;

    class OpenGLDevice : public Device
    {
      public:
        OpenGLDevice();

        Shader* createShader(const ShaderSource& shaderSource) const override;

        Texture* createTexture(const TextureSpec &textureSpec) const override;

        FramebufferAttachment *createFramebufferAttachment(const FramebufferAttachmentSpec &attachmentSpec) const override;

        virtual ~OpenGLDevice();

      private:

        FramebufferAttachment * createAttachmentUsingUserTexture(Texture* userTexture, const GLenum& type) const;
        FramebufferAttachment* createTextureBasedAttachment(const FramebufferAttachmentSpec& attachmentSpec) const;
        FramebufferAttachment* createRenderBufferAttachment(const FramebufferAttachmentSpec& attachmentSpec, const GLenum& type) const;

        OpenGLShaderFactory* shaderFactory;
    };
} // namespace blitz::ogl