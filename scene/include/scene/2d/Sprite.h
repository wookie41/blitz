#pragma once

#include <scene/2d/CanvasItem.h>

namespace blitz
{
    class Texture;

    struct Sprite : CanvasItem
    {
        Vector2i texRegionSize;
        Vector2i texRegionIndex;
        Vector2i spriteSize;
        Texture* texture;

        inline const CanvasItemType getType() const override { return CanvasItemType::SPRITE; }
    };
} // namespace blitz