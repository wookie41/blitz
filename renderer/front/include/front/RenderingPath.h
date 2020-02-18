#pragma once

#include <blitzcommon/NonCopyable.h>
#include <front/Precompiled.h>

namespace blitz
{
    struct Renderable;
    struct Light;

    class RenderingPath : public NonCopyable
    {
      public:
        RenderingPath() = default;

        virtual void addGeometry(Renderable* geometry) = 0;
        virtual void addUIElement(Renderable* geometry) = 0;
        virtual void addGeometry(Light* light) = 0;

        virtual ~RenderingPath() = default;
    }
} // namespace blitz