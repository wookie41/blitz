#pragma

#include <GL/glew.h>
#include <core/Framebuffer.h>

namespace blitz::ogl
{
    class OpenGLFramebuffer : public Framebuffer
    {
      public:

        void bind(const AccessOption& accessOption) override;
        void unbind() override;

    private:
        GLuint framebufferID;
        GLenum lastBindTarget;
        std::vector<GLenum> drawBuffers;
    };
} // namespace blitz::ogl