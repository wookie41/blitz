#include <unordered_map>

#include "GL/glew.h"
#include "blitzcommon/EnumClassHash.h"
#include "core/Buffer.h"
#include "core/Context.h"

namespace blitz
{
    class OpenGLContext : public Context
    {
      public:
        explicit OpenGLContext();
        ContextLock bindBuffers(const std::vector<BufferBinding>& bindings) override;

      protected:
        std::mutex contextMutex;

      private:
        std::unordered_map<void*, GLuint> buffersMapping;
        std::unordered_map<BufferBindTarget, uint16_t, EnumClassHash> targetsMapping;
    };
} // namespace blitz