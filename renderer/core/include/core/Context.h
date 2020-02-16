
#include <core/Precompiled.h>
#include <core/Buffer.h>

namespace blitz
{
    class Context;

    using std::function<void(Context*)> = ContextOperation;

    class BufferFiller;
    class VertexArray;
    class Framebuffer;

    class Context : private NonCopyable
    {
      public:

        void run(ContextOperation contextOperation);

        virtual Buffer* createBuffer(const BufferSpec& bufferSpec) = 0;
        virtual VertexArray* createVertexArray() = 0;
        virtual Framebuffer* createFramebuffer() = 0;
        virtual const BufferFiller* getBufferFiller() = 0;

        virtual ~Context() = default;

    protected:
        std::mutex selfMutex;
    };
} // namespace blitz