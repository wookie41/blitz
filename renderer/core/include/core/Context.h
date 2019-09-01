#pragma once

#include "Buffer.h"
#include "blitzcommon/Utils.h"
#include <mutex>

namespace blitz
{
    class Buffer;

    struct BufferBinding
    {
        const Buffer* buffer;
        const BufferBindTarget target;
    };

    class Context : private NonCopyable
    {
      public:
        virtual std::scoped_lock<std::mutex> bindBuffers(BufferBinding* bindings,
                                                         uint8_t len) = 0;
        virtual ~Context() = default;
    };
} // namespace blitz