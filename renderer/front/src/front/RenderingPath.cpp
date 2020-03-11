#include <core/Renderer.h>
#include <front/Camera.h>
#include <front/RenderingPath.h>

namespace blitz::front
{
    RenderingPath::RenderingPath(Renderer* renderer) : backend(renderer) {}
} // namespace blitz::front