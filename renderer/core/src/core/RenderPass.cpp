#include <core/RenderPass.h>

namespace blitz
{
    RenderPass::RenderPass(RenderState* state, Array<RenderCommand>* commands)
    : renderState(state), renderCommands(commands)
    {
    }

    const RenderState* RenderPass::getRenderState() const { return renderState; }

    RenderPass::~RenderPass() {}
} // namespace blitz
