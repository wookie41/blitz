#include <core/Framebuffer.h>
#include <core/RenderPass.h>
#include <core/Renderer.h>
#include <core/Shader.h>
#include <front/ForwardRenderingPath.h>
#include <front/Renderable.h>

namespace blitz
{
    ForwardRenderingPath::ForwardRenderingPath(Camera* cameraToRenderFrom,
                                               Renderer* renderer,
                                               const Framebuffer* targetFrameBuffer,
                                               const Shader* shaderToUse)
    : RenderingPath::RenderingPath(cameraToRenderFrom, renderer), framebuffer(targetFrameBuffer), shader(shaderToUse)
    {
    }

    void ForwardRenderingPath::render() {}

    void ForwardRenderingPath::addGeometry(Renderable* geometry) { geometryToRender.push_back(geometry); }

    void ForwardRenderingPath::addUIElement(Renderable* uiElement) { uiElementsToRender.push_back(uiElement); }

    void ForwardRenderingPath::addLight(Light* light) { lights.push_back(light); }
} // namespace blitz