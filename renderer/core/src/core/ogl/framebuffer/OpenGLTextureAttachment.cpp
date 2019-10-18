#include <GL/glew.h>
#include <core/ogl/framebuffer/OpenGLTextureAttachment.h>
#include <core/ogl/texture/OpenGLTexture.h>

namespace blitz::ogl
{
    OpenGLTextureAttachment::OpenGLTextureAttachment(OpenGLTexture* texture) : texture(texture) {}

    void OpenGLTextureAttachment::bind(const FramebufferAttachmentSpec& attachmentSpec)
    {
        if (texture == nullptr)
            return;

        GLenum target;

        switch (attachmentSpec.target)
        {
        case FramebufferAttachmentTarget::COLOR:
            target = static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + attachmentSpec.attachmentIdx);
            break;
        case FramebufferAttachmentTarget::DEPTH:
            target = GL_DEPTH_ATTACHMENT;
            break;
        case FramebufferAttachmentTarget::STENCIL:
            target = GL_STENCIL_ATTACHMENT;
            break;
        case FramebufferAttachmentTarget::DEPTH_STENCIL:
            target = GL_DEPTH_STENCIL_ATTACHMENT;
            break;
        }

        // TODO In future, we should allow for mipmap level to be specified
        switch (texture->getTextureType())
        {
        case TextureType::ONE_DIMENSIONAL:
            glFramebufferTexture1D(GL_FRAMEBUFFER, target, GL_TEXTURE_1D, texture->getTextureID(), 0);
            break;
        case TextureType::TWO_DIMENSIONAL:
            glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D, texture->getTextureID(), 0);
            break;
        case TextureType::THREE_DIMENSIONAL:
            glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D, texture->getTextureID(), 0);
            break;
        }
    }
} // namespace blitz::ogl