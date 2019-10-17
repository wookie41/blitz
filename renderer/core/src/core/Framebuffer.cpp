#include <core/Framebuffer.h>

static auto depthAttachmentDirty = 0b00000001;
static auto stencilAttachmentDirty = 0b00000010;
static auto depthStencilAttachmentDirty = 0b00000011;

namespace blitz
{
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

    void Framebuffer::setColorAttachment(uint16 colorAttachmentIdx, FramebufferAttachment* colorAttachment)
    {
        colorAttachments[colorAttachmentIdx] = colorAttachment;
    }
} // namespace blitz