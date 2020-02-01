#pragma once

#include <core/Precompiled.h>
#include <core/Framebuffer.h>

namespace blitz::ogl
{
    class OpenGLFramebuffer : public Framebuffer
    {
      public:

        OpenGLFramebuffer(GLuint id);

        void bind() override;
        void unbind() override;

        virtual ~OpenGLFramebuffer();

    private:
        GLuint framebufferID;
        std::vector<GLenum> drawBuffers;
    };
} // namespace blitz::ogl