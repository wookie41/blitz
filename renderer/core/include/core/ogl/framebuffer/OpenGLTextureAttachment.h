#pragma once

#include <core/FramebufferAttachment.h>

namespace blitz::ogl
{
    class OpenGLTexture;

    class OpenGLTextureAttachment: public FramebufferAttachment
    {
        friend class OpenGLDevice;
        friend class OpenGLShader;

    public:

        void bind(const AttachmentBindSpec &attachmentSpec) override;
        void *getData() override;

        ~OpenGLTextureAttachment() override;


    private:

        explicit OpenGLTextureAttachment(OpenGLTexture* texture, const GLenum& attachmenType, bool isTextureOwner);

        OpenGLTexture* texture;
        GLenum attachmentType;
        bool isTextureOwner;
    };
}