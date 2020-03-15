#pragma once

#include <scene/2d/Transform2D.h>

namespace blitz
{
    enum class CanvasItemType
    {
        SPRITE
    };

    struct CanvasItem;

    struct CanvasChild
    {
        CanvasItem* child  = nullptr;
        CanvasChild* next = nullptr;
    };

    struct CanvasItem
    {
        Transform2D transform;
        bool isVisible;
        CanvasItem* parent;
        CanvasChild* children; //linked list
        CanvasChild* childrenTail = nullptr;

        inline virtual const CanvasItemType& getType() const = 0;
    };
}