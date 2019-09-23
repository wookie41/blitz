#pragma once

#include <mutex>
#include <vector>
#include <functional>

#include "Buffer.h"
#include "blitzcommon/NonCopyable.h"


namespace blitz
{
    struct BufferBinding
    {
        Buffer* buffer;
        const BufferBindTarget target;
    };

    class Context;

    typedef std::function<void(Context*)> ContextOperation;

    class BufferFiller;
    class VertexArray;

    class Context : private NonCopyable
    {
      public:

        void run(ContextOperation contextOperation);

        virtual Buffer* createBuffer(const BufferSpec& bufferSpec) = 0;
        virtual VertexArray* createVertexArray() = 0;

        virtual const BufferFiller* getBufferFiller() = 0;

        virtual ~Context() = default;

    protected:
        std::mutex selfMutex;
    };
} // namespace blitz