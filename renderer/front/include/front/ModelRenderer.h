#pragma once
#include <core/RenderCommand.h>

namespace blitz
{
    struct Model;
}

namespace blitz::front
{
    class BasicModelRenderer
    {
      public:
        // whoever requested the renderable for the model is responsible for freeing the ptr
        Array<RenderCommand>* makeRenderable(const Model* model, Array<RenderCommand>* commandsBuffer = nullptr);
    };
} // namespace blitz::front