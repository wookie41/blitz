#pragma once

#include <front/Precompiled.h>
#include <front/RenderingPath.h>

namespace blitz
{
    class Shader;
    class Framebuffer;

    class ForwardRenderingPath : public RenderingPath
    {
      public:
        ForwardRenderingPath(Camera* cameraToRenderFrom, Renderer* renderer, const Framebuffer* targetFrameBuffer, const Shader* shaderToUser)

        void render() override;

        void addGeometry(Renderable* geometry) override;
        void addUIElement(Renderable* uiElement) override;
        void addLight(Light* light) override;

      private:
        const Framebuffer* framebuffer;
        const Shader* shader;

        std::vector<Renderable*> geometryToRender;
        std::vector<Renderable*> uiElementsToRender;
        std::vector<Light*> lights;
    }
} // namespace blitz