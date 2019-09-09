#include "core/Buffer.h"

namespace blitz
{
    UsageHint blitz::Buffer::getUsageHint() const { return usageHint; }

    Buffer::Buffer(const blitz::UsageHint& usageHint) : usageHint(usageHint) {}
}