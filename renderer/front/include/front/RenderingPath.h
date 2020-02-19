#pragma once

#include <front/Precompiled.h>

namespace blitz
{
    struct Renderable;
    struct Light;

    class Camera;
    class Renderer;

    class RenderingPath : public NonCopyable
    {
      public:
        explicit RenderingPath(Camera* cameraToRenderFrom, const Renderer* renderer);

        virtual void render() = 0;

        virtual void addGeometry(Renderable* geometry) = 0;
        virtual void addUIElement(Renderable* geometry) = 0;
        virtual void addLight(Light* light) = 0;

        virtual ~RenderingPath() = default;

      protected:
        Camera* camera;
        Renderer* backendRenderer;
    };
} // namespace blitz