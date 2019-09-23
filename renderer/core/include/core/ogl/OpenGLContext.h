#include "GL/glew.h"
#include "blitzcommon/HashUtils.h"
#include "core/Buffer.h"
#include "core/Context.h"


namespace blitz
{
    class OpenGLBufferFiller;

    class OpenGLContext : public Context
    {
      public:
        explicit OpenGLContext();

        Buffer* createBuffer(const BufferSpec& bufferSpec) override;
        VertexArray* createVertexArray() override;

        const BufferFiller* getBufferFiller() override;

        ~OpenGLContext() override;

      private:
        OpenGLBufferFiller* bufferFiller;
    };
} // namespace blitz