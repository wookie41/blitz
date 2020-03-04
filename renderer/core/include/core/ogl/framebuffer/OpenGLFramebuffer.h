#pragma once

#include <core/Framebuffer.h>
#include <core/Precompiled.h>

namespace blitz::ogl
{
    class OpenGLFramebuffer : public Framebuffer
    {
      public:
        OpenGLFramebuffer(const GLuint& id, const uint16& numColAttachments);

        void bind() override;
        void unbind() override;

        virtual ~OpenGLFramebuffer();

      private:
        GLuint framebufferID;
        GLenum* drawBuffers;
    };
} // namespace blitz::ogl