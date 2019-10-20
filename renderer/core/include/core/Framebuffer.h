#pragma once

#include <blitzcommon/NonCopyable.h>
#include <core/AccessOption.h>
#include <core/DataType.h>
#include <unordered_map>
#include <vector>

namespace blitz
{
    class FramebufferAttachment;

    class Framebuffer : public NonCopyable
    {
      public:
        virtual void bind(const AccessOption& accessOption) = 0;
        virtual void unbind() = 0;

        void setDepthAttachment(FramebufferAttachment* depthAttachment);
        void setStencilAttachment(FramebufferAttachment* stencilAttachment);
        void setDepthStencilAttachment(FramebufferAttachment* depthStencilAttachment);

        virtual // color attachment idx starts with 0
        void setColorAttachment(uint16 colorAttachmentIdx, FramebufferAttachment* colorAttachment);

        virtual ~Framebuffer();

      protected:
        Framebuffer() = default;

        uint8 dirtyFields = 0;

        FramebufferAttachment* depthAttachment = nullptr;
        FramebufferAttachment* stencilAttachment = nullptr;
        FramebufferAttachment* depthStencilAttachment  = nullptr;
        std::unordered_map<uint16, FramebufferAttachment*> colorAttachments;
        std::vector<uint16> newlyAddedAttachments;
    };
} // namespace blitz