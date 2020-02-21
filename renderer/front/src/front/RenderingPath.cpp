#include <front/RenderingPath.h>
#include <front/Camera.h>
#include <core/Renderer.h>

namespace blitz::front
{
    RenderingPath::RenderingPath(Camera* cameraToRenderFrom, blitz::Renderer* renderer)
    : camera(cameraToRenderFrom), backendRenderer(renderer)
    {
    }

    void RenderingPath::setViewPort(const ViewPort& viewPort)
    {
        this->viewPort = viewPort;
    };
} // namespace blitz