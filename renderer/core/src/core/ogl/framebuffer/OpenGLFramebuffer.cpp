#include <core/FramebufferAttachment.h>
#include <core/ogl/framebuffer/OpenGLFramebuffer.h>
#include <loguru.hpp>

namespace blitz::ogl
{
    OpenGLFramebuffer::OpenGLFramebuffer(GLuint id) : framebufferID(id) {}

    void OpenGLFramebuffer::bind(const AccessOption& accessOption)
    {
        GLenum framebufferTarget;
        switch (accessOption)
        {
        case AccessOption::READ:
            framebufferTarget = GL_READ_FRAMEBUFFER;
            break;
        case AccessOption::WRITE:
            framebufferTarget = GL_DRAW_FRAMEBUFFER;
            break;
        case AccessOption::READ_WRITE:
            framebufferTarget = GL_FRAMEBUFFER;
            break;
        }

        lastBindTarget = framebufferTarget;
        glBindFramebuffer(framebufferTarget, framebufferID);

        if (glCheckFramebufferStatus(framebufferTarget) != GL_FRAMEBUFFER_COMPLETE)
        {
            DLOG_F(ERROR, "[OpenGL] Framebuffer %d is incomplete", framebufferID);
            glBindFramebuffer(framebufferTarget, 0);
            return;
        }

        for (const auto& colorAttachmentIdx : newlyAddedAttachments)
        {
            const auto attachment = colorAttachments[colorAttachmentIdx];
            attachment->bind({ colorAttachmentIdx, FramebufferAttachmentTarget::COLOR });

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

    void OpenGLFramebuffer::unbind() { glBindFramebuffer(lastBindTarget, 0); }

    OpenGLFramebuffer::~OpenGLFramebuffer() { glDeleteFramebuffers(1, &framebufferID); }
} // namespace blitz::ogl
