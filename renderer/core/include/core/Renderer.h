#pragma once

#include <blitzcommon/NonCopyable.h>

namespace blitz
{
    class RenderPass;

    class Renderer: NonCopyable
    {
    public:

        virtual void issue(RenderPass* renderPass) = 0;
        virtual void render() = 0;
    };
}