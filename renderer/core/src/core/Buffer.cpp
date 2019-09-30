#include "core/Buffer.h"

namespace blitz
{
    UsageHint blitz::Buffer::getUsageHint() const { return usageHint; }

    Buffer::Buffer(const blitz::UsageHint& usageHint) : usageHint(usageHint) {}

    uint32_t Buffer::getSize() const { return size; }

    bool Buffer::IsReadable() const { return isReadable; }

    bool Buffer::IsWriteable() const { return isWriteable; }

    void Buffer::setSize(const uint32_t& size) { Buffer::size = size; }
} // namespace blitz