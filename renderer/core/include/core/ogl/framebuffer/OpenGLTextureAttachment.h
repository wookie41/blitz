#pragma once

#include <core/FramebufferAttachment.h>

namespace blitz::ogl
{
    class OpenGLTexture;

    class OpenGLTextureAttachment: public FramebufferAttachment
    {
    public:
        explicit OpenGLTextureAttachment(OpenGLTexture* texture);
        void bind(const FramebufferAttachmentSpec &attachmentSpec);

    private:
        OpenGLTexture* texture;
    };
}