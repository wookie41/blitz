#include <core/Buffer.h>
#include <core/Context.h>
#include <core/Precompiled.h>
#include <core/ogl/texture/OpenGLSyncReadTexture.h>

namespace blitz::ogl
{
    class OpenGLBufferFiller;

    class OpenGLContext : public Context
    {
      public:
        explicit OpenGLContext();

        Buffer* createBuffer(const BufferSpec& bufferSpec) override;
        VertexArray* createVertexArray(const uint8& numAttributes) override;
        Framebuffer* createFramebuffer(const uint16& numColorAttachments) override;

        const BufferFiller* getBufferFiller() override;

        ~OpenGLContext() override;

      private:
        OpenGLBufferFiller* bufferFiller;
    };
} // namespace blitz::ogl