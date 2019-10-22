#pragma once

#include <core/DataType.h>

namespace blitz
{
    class Texture;

    enum class FramebufferAttachmentType
    {
        RGB,
        RGBA,
        STENCIL,
        DEPTH,
        DEPTH_STENCIL
    };

    struct FramebufferAttachmentSpec
    {
        // pass a texture if you don't want the engine to create a render target
        // note that if you do this, you'll have make sure the dimensions and internal format match
        Texture* texture;
        bool readable;
        uint8 numberOfDimensions;
        Vector3i dimensions;
        FramebufferAttachmentType type;
    };
} // namespace blitz