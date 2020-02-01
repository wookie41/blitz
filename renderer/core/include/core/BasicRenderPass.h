#pragma once

#include <core/Precompiled.h>
#include <core/RenderPass.h>

namespace blitz
{
    class BasicRenderPass : public RenderPass
    {
      public:

        explicit BasicRenderPass(RenderState* renderState);

        void finish() override;

        void add(RenderCommand* renderCommand) override;
        RenderCommand* getNextCommand() override;

    private:
        bool isFinished = false;
        std::deque<RenderCommand*> renderCommands;
    };
} // namespace blitz