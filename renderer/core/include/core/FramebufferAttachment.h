#pragma once

#include "DataType.h"

namespace blitz
{
    enum class FramebufferAttachmentTarget
    {
        COLOR,
        DEPTH,
        STENCIL,
        DEPTH_STENCIL
    };

    struct FramebufferAttachmentSpec
    {
        // 0 for stencil and depth
        uint16 attachmentIdx;
        FramebufferAttachmentTarget target;
    };

    class FramebufferAttachment
    {
      public:
        virtual void bind(const FramebufferAttachmentSpec& attachmentSpec) = 0;
        virtual ~FramebufferAttachment() = default;
    };
} // namespace blitz