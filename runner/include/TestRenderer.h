#pragma once

#include <front/Precompiled.h>
#include <front/ModelRenderer.h>
#include <resources/model/ModelLoader.h>
#include <resources/texture/TextureLoader.h>
#include <front/RenderingPath.h>
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
    class Camera;

    class TestRenderer
    {
      public:
        TestRenderer(Window* window, Camera* camera, const ViewPort& viewPort);
        RenderList* getTestRenderList();
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
        Array<blitz::UniformState>* cubeUniforms;
        Array<RenderCommand>* renderCubeCommands;
        RenderList* testRenderList;
    };
} // namespace blitz::front