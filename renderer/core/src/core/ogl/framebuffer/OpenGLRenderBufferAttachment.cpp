#include <core/ogl/framebuffer/OpenGLRenderBufferAttachment.h>

namespace blitz::ogl
{
    OpenGLRenderBufferAttachment::OpenGLRenderBufferAttachment(GLuint rboID, GLenum type) : rboID(rboID), type(type) {}

    void* OpenGLRenderBufferAttachment::getData()
    {
        return nullptr; // RBOs are not readable
    }

    void OpenGLRenderBufferAttachment::bind(const AttachmentBindSpec& bindSpec)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, rboID);
    }

    OpenGLRenderBufferAttachment::~OpenGLRenderBufferAttachment() { glDeleteRenderbuffers(1, &rboID); }
} // namespace blitz::ogl