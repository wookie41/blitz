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

        Renderable* render() override;

      private:
        Renderable* render(const Model* model) const;

        std::vector<Model*> modelsToRender;
    };
} // namespace blitz::front