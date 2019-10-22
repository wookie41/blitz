#include <core/FramebufferAttachment.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>
#include <loguru.hpp>

namespace blitz::ogl
{
    OpenGLFramebuffer::OpenGLFramebuffer(GLuint id) : framebufferID(id) {}

    void OpenGLFramebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            DLOG_F(ERROR, "[OpenGL] Framebuffer %d is incomplete", framebufferID);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return;
        }

        for (const auto& colorAttachmentIdx : newlyAddedAttachments)
        {
            const auto attachment = colorAttachments[colorAttachmentIdx];
            attachment->bind({ colorAttachmentIdx });

            std::vector<GLenum> boundColorAttachments = {};
            for (const auto& colorAttachment : colorAttachments)
                boundColorAttachments.push_back(colorAttachment.first);

            std::sort(boundColorAttachments.begin(), boundColorAttachments.end());

            drawBuffers.clear();
            for (int i = 0; i < boundColorAttachments[0]; ++i)
                drawBuffers.push_back(0);

            for (auto it = boundColorAttachments.begin(); it != boundColorAttachments.end(); ++it)
            {
                drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + *it);
                for (int notBoundAttachment = (*it) + 1; notBoundAttachment < (*it) + 1; ++notBoundAttachment)
                    drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + notBoundAttachment);
            }
        }

        glDrawBuffers(drawBuffers.size(), drawBuffers.data());
    }

    void OpenGLFramebuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    OpenGLFramebuffer::~OpenGLFramebuffer() { glDeleteFramebuffers(1, &framebufferID); }
} // namespace blitz::ogl
