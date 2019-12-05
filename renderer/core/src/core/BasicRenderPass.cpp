#include <core/BasicRenderPass.h>

namespace blitz
{
    BasicRenderPass::BasicRenderPass(RenderState* renderState) : RenderPass(renderState) {}

    void BasicRenderPass::add(RenderCommand* renderCommand)
    {
        if (!isFinished)
            renderCommands.push_back(renderCommand);
    }

    RenderCommand* BasicRenderPass::getNextCommand()
    {
        if (renderCommands.empty() || !isFinished)
            return nullptr;

        auto nextCommand = renderCommands.front();
        renderCommands.pop_front();
        return nextCommand;
    }

    void BasicRenderPass::finish() { isFinished = true; }
} // namespace blitz