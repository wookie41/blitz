#pragma once

#include <core/RenderPass.h>

namespace blitz
{
    class BasicRenderPass : public RenderPass
    {
      public:
        BasicRenderPass(const RenderState* renderState, const Array<RenderCommand>* commands);

        void prepare() override;

        RenderCommand* getNextCommand() override;
    private:
        uint64 commandsIssued = 0;
    };
} // namespace blitz