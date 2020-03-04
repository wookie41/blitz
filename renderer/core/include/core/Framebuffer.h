#pragma once

#include <core/Precompiled.h>

namespace blitz
{
    class FramebufferAttachment;

    class Framebuffer : public NonCopyable
    {
      public:
        virtual void bind() = 0;
        virtual void unbind() = 0;

        void setDepthAttachment(FramebufferAttachment* depthAttachment);
        void setStencilAttachment(FramebufferAttachment* stencilAttachment);
        void setDepthStencilAttachment(FramebufferAttachment* depthStencilAttachment);

        //The framebuffer must be bound for this method to have effect
        void setColorAttachment(const uint16& colorAttachmentIdx, FramebufferAttachment* colorAttachment);
        virtual ~Framebuffer();

      protected:
        explicit Framebuffer(const uint16& numColAttachments);

        uint8 dirtyFields = 0;

        uint16 numColorAttachments;
        FramebufferAttachment* depthAttachment = nullptr;
        FramebufferAttachment* stencilAttachment = nullptr;
        FramebufferAttachment* depthStencilAttachment = nullptr;
        FramebufferAttachment** colorAttachments = nullptr;
    };
} // namespace blitz