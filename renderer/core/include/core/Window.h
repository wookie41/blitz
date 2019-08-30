#pragma once

#include "blitzcommon/Utils.h"

#include "core/RenderCommand.h"
#include "core/RenderPass.h"
#include "core/RenderState.h"

namespace blitz
{
    struct WindowDef
    {
        uint32_t width, height;
        const char* title;
    };

    class Window : private NonCopyable
    {
      public:
        virtual void issue(RenderPass* renderPass) = 0;

        // render should process all of the RenderPasses that have been issued
        // since the last render was called
        virtual void render() = 0;

        virtual ~Window() = default;
    };
} // namespace blitz