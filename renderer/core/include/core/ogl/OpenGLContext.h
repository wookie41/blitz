#include <unordered_map>

#include "GL/glew.h"
#include "blitzcommon/EnumClassHash.h"
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

        ContextLock bindBuffers(std::vector<BufferBinding>& bindings) override;

        ~OpenGLContext() override;

      protected:
        std::mutex contextMutex;

      private:

        std::mutex selfMutex;
        std::unordered_map<BufferBindTarget, uint16_t, EnumClassHash> targetsMapping;

        OpenGLBufferFiller* bufferFiller;
    };
} // namespace blitz