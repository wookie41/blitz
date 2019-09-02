#pragma once

#include <mutex>
#include <vector>

#include "Buffer.h"
#include "blitzcommon/NonCopyable.h"

namespace blitz
{
    struct BufferBinding
    {
        const Buffer* buffer;
        const BufferBindTarget target;
    };

    typedef std::unique_lock<std::mutex> ContextLock;

    class Context : private NonCopyable
    {
      public:
        virtual ContextLock bindBuffers(const std::vector<BufferBinding>& bindings) = 0;
        virtual ~Context() = default;
    };
} // namespace blitz