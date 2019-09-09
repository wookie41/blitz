#pragma once

#include <mutex>
#include <vector>

#include "Buffer.h"
#include "blitzcommon/NonCopyable.h"

namespace blitz
{
    struct BufferBinding
    {
        Buffer* buffer;
        const BufferBindTarget target;
    };

    typedef std::unique_lock<std::mutex> ContextLock;

    class BufferFiller;

    class Context : private NonCopyable
    {
      public:
        virtual const BufferFiller* getBufferFiller() = 0;

        virtual Buffer* createBuffer(BufferSpec bufferSpec) = 0;
        virtual ContextLock bindBuffers(std::vector<BufferBinding>& bindings) = 0;
        virtual ~Context() = default;
    };
} // namespace blitz