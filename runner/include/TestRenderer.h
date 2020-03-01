#pragma once

#include <front/Precompiled.h>
#include <front/ModelRenderer.h>
#include <resources/model/ModelLoader.h>
#include <resources/texture/TextureLoader.h>

namespace blitz
{
    class Window;
    class VertexArray;
    class Shader;
    class Texture;
    struct Model;
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
        blitz::Model* rockModel;
        blitz::VertexArray* basicVertexArray;
        blitz::Shader* shader;
        blitz::Texture* tex;
        bool shouldUseTexture;
        blitz::ogl::OpenGLTextureSampler* sampler;
        blitz::Vector3f* color;
        BasicModelRenderer modelRenderer;
        TextureLoader textureLoader;
        ModelLoader* modelLoader;
    };
} // namespace blitz::front