#include <GL/glew.h>
#include <core/ogl/framebuffer/OpenGLTextureAttachment.h>
#include <core/ogl/texture/OpenGLTexture.h>

namespace blitz::ogl
{
    OpenGLTextureAttachment::OpenGLTextureAttachment(OpenGLTexture* texture, const GLenum& attachmentType)
    : texture(texture), attachmentType(attachmentType)
    {
    }

    void OpenGLTextureAttachment::bind(const AttachmentBindSpec& attachmentSpec)
    {
        if (texture == nullptr)
            return;

        GLenum attachmentTarget = attachmentType;

        if (attachmentTarget == GL_COLOR_ATTACHMENT0)
            attachmentTarget = static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + attachmentSpec.attachmentIdx);

        // TODO In future, we should allow for mipmap level to be specified
        switch (texture->getTextureType())
        {
        case TextureType::ONE_DIMENSIONAL:
            glFramebufferTexture1D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_1D, texture->getTextureID(), 0);
            break;
        case TextureType::TWO_DIMENSIONAL:
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, texture->getTextureID(), 0);
            break;
        case TextureType::THREE_DIMENSIONAL:
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_3D, texture->getTextureID(), 0);
            break;
        }
    }

    void *OpenGLTextureAttachment::getData()
    {
        return texture->download(nullptr, 0);
    }
} // namespace blitz::ogl