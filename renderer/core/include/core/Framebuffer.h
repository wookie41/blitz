#pragma once

#include <blitzcommon/NonCopyable.h>
#include <core/DataType.h>
#include <unordered_map>

namespace blitz
{
    class FramebufferAttachment;

    class Framebuffer : public NonCopyable
    {
      public:
        virtual void bind() = 0;

        void setDepthAttachment(FramebufferAttachment* depthAttachment);
        void setStencilAttachment(FramebufferAttachment* stencilAttachment);
        void setDepthStencilAttachment(FramebufferAttachment* depthStencilAttachment);

        // color attachment idx starts with 0
        void setColorAttachment(uint16 colorAttachmentIdx, FramebufferAttachment* colorAttachment);

      protected:
        Framebuffer() = default;

        uint8 dirtyFields = 0;

        FramebufferAttachment* depthAttachment;
        FramebufferAttachment* stencilAttachment;
        FramebufferAttachment* depthStencilAttachment;
        std::unordered_map<uint16, FramebufferAttachment*> colorAttachments;
    };
} // namespace blitz