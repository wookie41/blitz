#pragma once

#include <front/Renderer.h>

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
    class TestRenderer : public Renderer
    {
      public:
        TestRenderer(Window* window);
        Renderable* render();
        Shader* getShader() const;

      private:
        blitz::VertexArray* basicVertexArray;
        blitz::Shader* shader;
        blitz::Texture* tex;
        bool shouldUseTextureForFirstTriangle;
        blitz::ogl::OpenGLTextureSampler* sampler;
        blitz::Vector3f* triangleColor;
        bool shouldUseTextureForSecondTriangle;
    };
} // namespace blitz::front