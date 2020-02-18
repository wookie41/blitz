#include <front/RenderingPath.h>

namespace blitz
{
    RenderingPath::RenderingPath(Camera* cameraToRenderFrom, const Renderer* renderer)
    : camer(cameraToRenderFrom), backendRenderer(renderer)
    {
    }
} // namespace blitz