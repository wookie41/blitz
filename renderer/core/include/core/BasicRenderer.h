#pragma once

#include <core/Precompiled.h>
#include <core/Renderer.h>
#include <core/RenderCommand.h>

namespace blitz
{
    class Shader;

    class BasicRenderer: public Renderer
    {
    public:

        void issue(RenderPass *renderPass) override;
        void render(Window* window) override;

    private:

        void updateUniforms(Shader* shader, const std::vector<UniformState*>& uniformsState);

        template <typename T>
        void updateUniform(Shader* shader, const hash& uniformNameHash, void* value);

        std::mutex mx;
        std::deque<RenderPass*> renderPasses;
    };
}