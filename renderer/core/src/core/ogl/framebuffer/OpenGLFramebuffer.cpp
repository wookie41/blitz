#include <core/FramebufferAttachment.h>
#include <core/ogl/OpenGLDataType.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>

namespace blitz::ogl
{
    OpenGLFramebuffer::OpenGLFramebuffer(const GLuint& id, const uint16& numColAttachments)
    : Framebuffer::Framebuffer(numColorAttachments), framebufferID(id)
    {
        if (id == 0)
        {
            drawBuffers = new GLenum;
            *drawBuffers = GL_COLOR_ATTACHMENT0;
            return;
        }

        drawBuffers = new GLenum(numColorAttachments);
        for (uint16 colAttachmentIdx = 0; colAttachmentIdx < numColorAttachments; ++colAttachmentIdx)
        {
            drawBuffers[colAttachmentIdx] = GL_COLOR_ATTACHMENT0 + colAttachmentIdx;
        }
    }

    void OpenGLFramebuffer::bind()
    {
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

        if (framebufferID > 0)
        {
            glDrawBuffers(numColorAttachments, drawBuffers);
        }
    }

    void OpenGLFramebuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        delete drawBuffers;
        if (framebufferID > 0)
        {
            glDeleteFramebuffers(1, &framebufferID);
        }
    }
} // namespace blitz::ogl
