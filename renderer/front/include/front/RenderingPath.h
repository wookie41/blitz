#pragma once

#include <front/Precompiled.h>
#include <core/RenderState.h>
#include <core/RenderCommand.h>

namespace blitz
{
    class Renderer;
    class Framebuffer;
} // namespace blitz

namespace blitz::front
{
    struct Renderable;
    struct Light;

    class Camera;

    struct RenderList
    {
        const ViewPort* viewPort;
        const Camera* camera = nullptr;
        const Framebuffer* framebuffer = nullptr; 
        const Array<RenderCommand>* geometry = nullptr;
        const Array<Light*>* lights = nullptr;
    };

    class RenderingPath : public NonCopyable
    {
      public:
        RenderingPath(Renderer* renderer);

        virtual void render(RenderList* renderList) = 0;

        virtual ~RenderingPath() = default;

      protected:
        inline Matrix4f calculateProjectionMatrix(const ViewPort& viewPort, const Projection& projection, const float& fov)
        {
            return projection == Projection::PERSPECTIVE ?
                   Matrix4f::Perspective(toRadians(fov), (float)viewPort.width / (float)viewPort.height, viewPort.near,
                                         viewPort.far) :
                   Matrix4f::Ortho(viewPort.x, viewPort.width, viewPort.y, viewPort.height, viewPort.near, viewPort.far);
        }

        Renderer* backend;
    };
} // namespace blitz::front