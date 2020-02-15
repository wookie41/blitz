#pragma once

#include <front/Renderer.h>

namespace blitz
{
    struct Model;
}

namespace blitz::front
{
    class BasicModelRenderer : public Renderer
    {
      public:
        BasicModelRenderer(std::vector<Model*>&& models);
        ~BasicModelRenderer() override = default;

        std::vector<RenderCommand*> produceCommands() override;

      private:
        std::vector<RenderCommand*> createCommandsFor(const Model* model) const;

        std::vector<Model*> modelsToRender;
    };
} // namespace blitz::front