#include <core/FramebufferAttachment.h>
#include <core/ogl/OpenGLDataType.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>

namespace blitz::ogl
{
    OpenGLFramebuffer::OpenGLFramebuffer(const GLuint& id, const uint16& numColAttachments)
    : Framebuffer::Framebuffer(numColorAttachments), framebufferID(id)
    {
        drawBuffers = new GLenum(numColorAttachments);
        for (uint16 colAttachmentIdx = 0; colAttachmentIdx < numColorAttachments; ++colorAttachmentIdx)
        {
            drawBuffers[colAttachmentIdx] = GL_COLOR_ATTACHMENT0 + colAttachmentIdx;
        }
    }

    void OpenGLFramebuffer::bind()
    {
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
        glDrawBuffers(numColorAttachments, drawBuffers);
    }

    void OpenGLFramebuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        delete drawBuffers;
        glDeleteFramebuffers(1, &framebufferID);
    }
} // namespace blitz::ogl
