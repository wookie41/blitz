#include <core/RenderPass.h>
#include <core/RenderState.h>

namespace blitz
{
    RenderPass::RenderPass(RenderState* renderState) : renderState(renderState) {}

    RenderPass::~RenderPass() { delete renderState; }
} // namespace blitz
