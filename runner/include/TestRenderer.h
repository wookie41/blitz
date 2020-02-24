#pragma once

#include <front/Precompiled.h>

namespace blitz
{
    class Window;
    class VertexArray;
    class Shader;
    class Texture;
    namespace ogl
    {
        class OpenGLTextureSampler;
    }
} // namespace blitz

namespace blitz::front
{
    struct Renderable;

    class TestRenderer
    {
      public:
        TestRenderer(Window* window);
        Renderable* getTestRenderable();
        Shader* getShader() const;

      private:
        blitz::VertexArray* basicVertexArray;
        blitz::Shader* shader;
        blitz::Texture* tex;
        bool shouldUseTexture;
        blitz::ogl::OpenGLTextureSampler* sampler;
        blitz::Vector3f* color;
    };
} // namespace blitz::front