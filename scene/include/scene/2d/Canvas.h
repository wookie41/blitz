#pragma once

#include <scene/2d/CanvasItem.h>

namespace blitz
{
    struct Canvas : CanvasItem
    {
        Canvas() = default;
        inline const CanvasItemType getType() const override { return CanvasItemType::CANVAS; }
    };
} // namespace blitz