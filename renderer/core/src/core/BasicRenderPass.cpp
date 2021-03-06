#include <core/BasicRenderPass.h>
#include <core/RenderState.h>

namespace blitz
{
    BasicRenderPass::BasicRenderPass(const RenderState* renderState, const Array<RenderCommand>* commands)
    : RenderPass(renderState, commands)
    {
    }

    void BasicRenderPass::prepare() {}

    RenderCommand* BasicRenderPass::getNextCommand()
    {
        if (commandsIssued == renderCommands->getSize())
        {
            return nullptr;
        }

        return renderCommands->get(commandsIssued++);
    }
} // namespace blitz