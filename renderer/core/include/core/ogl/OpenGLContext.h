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

        const BufferFiller* getBufferFiller() override;

        Buffer* createBuffer(BufferSpec bufferSpec) override;

        ~OpenGLContext() override;

      private:

        OpenGLBufferFiller* bufferFiller;
    };
} // namespace blitz