#include <core/Context.h>

namespace blitz
{
    void Context::run(ContextOperation contextOperation)
    {
        auto selfLock = std::lock_guard(selfMutex);
        contextOperation(this);
    }
} // namespace blitz