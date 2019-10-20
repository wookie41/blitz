#pragma

#include <GL/glew.h>
#include <core/Framebuffer.h>

namespace blitz::ogl
{
    class OpenGLFramebuffer : public Framebuffer
    {
      public:

        OpenGLFramebuffer(GLuint id);

        void bind(const AccessOption& accessOption) override;
        void unbind() override;

        virtual ~OpenGLFramebuffer();

    private:
        GLuint framebufferID;
        GLenum lastBindTarget;
        std::vector<GLenum> drawBuffers;
    };
} // namespace blitz::ogl