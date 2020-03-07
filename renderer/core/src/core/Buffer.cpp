#include "core/Buffer.h"

namespace blitz
{
    UsageHint blitz::Buffer::getUsageHint() const { return usageHint; }

    Buffer::Buffer(const blitz::UsageHint& usageHint) : usageHint(usageHint) {}

    size_t Buffer::getSizeInBytes() const { return size; }

    bool Buffer::IsReadable() const { return isReadable; }

    bool Buffer::IsWriteable() const { return isWriteable; }

    void Buffer::setSize(const size_t& sizeInBytes) { Buffer::size = sizeInBytes; }
} // namespace blitz