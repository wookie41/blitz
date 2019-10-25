#include <core/RenderPass.h>
#include <core/RenderState.h>

namespace blitz
{
    RenderPass::RenderPass(RenderState* renderState) : renderState(renderState) {}

    RenderPass::~RenderPass() { delete renderState; }

    const RenderState& RenderPass::getRenderState() const { return *renderState; }
} // namespace blitz
