#pragma once

#include <core/FramebufferAttachment.h>
#include <GL/glew.h>

namespace blitz::ogl
{
    class OpenGLTexture;

    class OpenGLTextureAttachment: public FramebufferAttachment
    {
    public:

        explicit OpenGLTextureAttachment(OpenGLTexture* texture, const GLenum& attachmenType);
        void bind(const AttachmentBindSpec &attachmentSpec);

        void *getData() override;

    private:
        OpenGLTexture* texture;
        GLenum attachmentType;
    };
}