#pragma once

#include <core/RenderState.h>
#include <front/Precompiled.h>


namespace blitz
{
    class Renderer;
}

namespace blitz::front
{
    struct Renderable;
    struct Light;

    class Camera;

    class RenderingPath : public NonCopyable
    {
      public:
        RenderingPath(Camera* cameraToRenderFrom, blitz::Renderer* renderer);

        void setViewPort(const ViewPort& viewPort);

        virtual void render() = 0;

        virtual void addGeometry(Renderable* geometry) = 0;
        virtual void addUIElement(Renderable* geometry) = 0;
        virtual void addLight(Light* light) = 0;

        virtual ~RenderingPath() = default;

      protected:
        inline Matrix4f RenderingPath::calculateProjectionMatrix(const Projection& projection, const float& fov)
        {
            return projection == Projection::PERSPECTIVE ?
                   Matrix4f::Perspective(fov, viewPort.width / viewPort.height, viewPort.near, viewPort.far) :
                   Matrix4f::Ortho(viewPort.x, viewPort.x + viewPort.width, viewPort.y, viewPort.y + viewPort.height,
                                   viewPort.near, viewPort.far);
        }

        ViewPort viewPort;
        Camera* camera;
        blitz::Renderer* backendRenderer;
    };
} // namespace blitz::front