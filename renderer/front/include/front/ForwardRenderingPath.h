#pragma once

#include <front/Precompiled.h>
#include <front/RenderingPath.h>

namespace blitz
{
    class Shader;
    class Framebuffer;
}

namespace blitz::front
{

    class ForwardRenderingPath : public RenderingPath
    {
      public:
        ForwardRenderingPath(Camera* cameraToRenderFrom, blitz::Renderer* renderer, Framebuffer* targetFrameBuffer, Shader* shaderToUse);

        void render() override;

        void addGeometry(Renderable* geometry) override;
        void addUIElement(Renderable* uiElement) override;
        void addLight(Light* light) override;

      private:

        Framebuffer* framebuffer;
        Shader* shader;

        std::vector<Renderable*> geometryToRender;
        std::vector<Renderable*> uiElementsToRender;
        std::vector<Light*> lights;
    };
} // namespace blitz