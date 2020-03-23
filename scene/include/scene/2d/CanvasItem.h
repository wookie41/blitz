#pragma once

#include <scene/2d/Transform2D.h>
#include <front/Material.h>

namespace blitz
{
    enum class CanvasItemType
    {
        SPRITE,
        CANVAS
    };

    struct CanvasItem;

    struct CanvasChild
    {
        CanvasItem* child = nullptr;
        CanvasChild* next = nullptr;
    };

    struct CanvasItem
    {
        CanvasItem() = default;
        virtual ~CanvasItem() = default;

        Transform2D transform;
        bool isVisible;
        CanvasItem* parent;
        CanvasChild* children; // linked list
        CanvasChild* childrenTail = nullptr;
        Material* material;

        inline virtual const CanvasItemType getType() const = 0;
    };
} // namespace blitz