#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    struct AttachmentBindSpec
    {
        // 0 for stencil and depth
        uint16 attachmentIdx;
    };

    class FramebufferAttachment
    {
      public:
        virtual void* getData() = 0;
        virtual void bind(const AttachmentBindSpec& bindSpec) = 0;
        virtual ~FramebufferAttachment() = default;
    };
} // namespace blitz