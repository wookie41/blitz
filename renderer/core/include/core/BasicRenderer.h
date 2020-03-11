#pragma once

#include <core/Precompiled.h>
#include <core/RenderCommand.h>
#include <core/Renderer.h>

namespace blitz
{
    class Shader;

    class BasicRenderer : public Renderer
    {
      public:
        void issue(RenderPass* renderPass) override;
        void render() override;

      private:
        void updateUniforms(Shader* shader, Array<UniformState>* uniformsState);

        template <typename T>
        void updateUniform(Shader* shader, const hash& uniformNameHash, void* value);

        std::mutex mx;
        std::deque<RenderPass*> renderPasses;
    };
} // namespace blitz