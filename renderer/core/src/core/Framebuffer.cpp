#include <core/Framebuffer.h>
#include <core/FramebufferAttachment.h>

namespace blitz
{
    static uint8 depthAttachmentDirty = 0b00000001;
    static uint8 stencilAttachmentDirty = 0b00000010;
    static uint8 depthStencilAttachmentDirty = 0b00000011;

    Framebuffer::Framebuffer(const uint16& numColAttachments)
    {
        numColorAttachments = numColAttachments;
        colorAttachments = new FramebufferAttachment*[numColAttachments];
    }

    void Framebuffer::setDepthAttachment(FramebufferAttachment* depthAttachment)
    {
        dirtyFields |= depthAttachmentDirty;
        this->depthAttachment = depthAttachment;
    }

    void Framebuffer::setStencilAttachment(FramebufferAttachment* stencilAttachment)
    {
        dirtyFields |= stencilAttachmentDirty;
        this->stencilAttachment = stencilAttachment;
    }

    void Framebuffer::setDepthStencilAttachment(FramebufferAttachment* depthStencilAttachment)
    {
        dirtyFields |= depthStencilAttachmentDirty;
        this->depthStencilAttachment = depthStencilAttachment;
    }

    void Framebuffer::setColorAttachment(const uint16& colorAttachmentIdx, FramebufferAttachment* colorAttachment)
    {
        assert(colorAttachmentIdx < numColorAttachments);
        colorAttachments[colorAttachmentIdx] = colorAttachment;
        colorAttachment->bind({ colorAttachmentIdx });
    }

    Framebuffer::~Framebuffer()
    {
        delete depthAttachment;
        delete stencilAttachment;
        delete depthStencilAttachment;
        for (uint16 attachmentIdx = 0; attachmentIdx < numColorAttachments; ++attachmentIdx)
        {
            delete colorAttachments[attachmentIdx];
        }
        delete colorAttachments;
    }
} // namespace blitz