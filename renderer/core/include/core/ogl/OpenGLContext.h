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
        VertexArray* createVertexArray(const uint& numAttributes) override;
        Framebuffer* createFramebuffer() override;


        const BufferFiller* getBufferFiller() override;

        ~OpenGLContext() override;

      private:
        OpenGLBufferFiller* bufferFiller;
    };
} // namespace blitz::ogl