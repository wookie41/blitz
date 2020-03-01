#pragma once

namespace blitz
{
    struct Model;
}

namespace blitz::front
{
    struct Renderable;

    class BasicModelRenderer
    {
      public:
        // whoever requested the renderable for the model is responsible for freeing the ptr
        Renderable* makeRenderable(const Model* model);
    };
} // namespace blitz::front