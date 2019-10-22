#pragma once

#include <core/FramebufferAttachment.h>
#include <GL/glew.h>

namespace blitz::ogl
{
    class OpenGLRenderBufferAttachment: public FramebufferAttachment
    {
    public:
        friend class OpenGLDevice;

        OpenGLRenderBufferAttachment(GLuint rboID, GLenum type);

        void *getData() override;

        void bind(const AttachmentBindSpec &bindSpec) override;

        ~OpenGLRenderBufferAttachment() override;

    private:
        GLuint rboID;
        GLenum type;
    };
}
