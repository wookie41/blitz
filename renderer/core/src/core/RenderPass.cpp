#include <core/RenderPass.h>

namespace blitz
{
    RenderPass::RenderPass(const RenderState* state, const Array<RenderCommand>* commands)
    : renderState(state), renderCommands(commands)
    {
    }

    const RenderState* RenderPass::getRenderState() const { return renderState; }

    RenderPass::~RenderPass() {}
} // namespace blitz
