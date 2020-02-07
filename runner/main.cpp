#include <core/Device.h>
#include <core/Logger.h>

#include <core/Shader.h>
#include <core/ShaderSource.h>
#include <core/VertexArray.h>

#include "core/RenderCommand.h"
#include "core/RenderState.h"
#include <core/BasicRenderPass.h>
#include <core/Renderer.h>
#include <core/Window.h>
#include <iostream>
#include <resources/texture/STBImage2DTextureLoader.h>
#include <core/ogl/uniforms/OpenGLSamplerUniformVariable.h>
#include <core/ogl/texture/OpenGLTextureSampler.h>
#include <resources/ResourcesManager.h>
#include <resources/texture/STBImage2DTextureLoader.h>
#include <resources/model/Model.h>
#include <resources/model/AssimpModelLoader.h>
#include <resources/RefCountedResourceManager.h>
#include <front/ModelRenderer.h>

char* v = "#version 330 core\n"
          "layout (location = 0) in vec3 pos;\n"
          "layout (location = 1) in vec2 texCoords;\n"
          "out vec2 TexCoords;\n"
          "void main()\n"
          "{\n"
          "\n"
          "    TexCoords = texCoords;\n"
          "    gl_Position = vec4(pos * 0.001f, 1.0);\n"
          "}";


char* f = "#version 330 core\n"
          "layout (location = 0) out vec4 FragColor;  \n"
          "\n"
          "in vec2 TexCoords;"
          "uniform vec3 color;\n"
          "uniform sampler2D tex;\n"
          "uniform bool useTexture;\n"
          "void main()\n"
          "{\n"
          "if (useTexture)\n"
          "{\n"
          " FragColor = texture(tex, TexCoords);\n"
          "}\n"
          "else"
          "{\n"
          " FragColor = vec4(color, 1.f);\n"
          "}\n"
          "}";

extern blitz::Device* BLITZ_DEVICE;
extern blitz::Renderer* BLITZ_RENDERER;

#include <assimp/scene.h>

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);

    auto windowDef = blitz::WindowDef{ 0, 0, 400, 400, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    window->show();

    float vertexData[] = {
        -0.9f, -0.5f, 0.0f, 0.f, 0.f, // left
        -0.0f, -0.5f, 0.0f, .5f, 1.f, // right
        -0.45f, 0.5f, 0.0f, 1.f, 0.f, // top
        // second triangle
        0.0f, -0.5f, 0.0f, 0.f, 0.f, // left
        0.9f, -0.5f, 0.0f, 0.f, 0.f, // right
        0.45f, 0.5f, 0.0f, 0.f, 0.f, // top
    };

    auto vertexBuffer = window->getContext().createBuffer(
    { sizeof(vertexData), blitz::UsageHint::STATIC, 0, blitz::BindHint::VERTEX, vertexData, false, true });

    blitz::VertexArray* basicVertexArray = window->getContext().createVertexArray();
    basicVertexArray->addAttribute({ vertexBuffer, "pos", blitz::DataType::FLOAT, 3, false, 5 * sizeof(float), 0, 0 });
    basicVertexArray->addAttribute({ vertexBuffer, "texCoords", blitz::DataType::FLOAT, 2, false, 5 * sizeof(float), 3 * sizeof(float), 0 });

    blitz::ShaderSource shaderSource = { "myshader", v, nullptr, f };
    blitz::Shader* shader = BLITZ_DEVICE->createShader(shaderSource);

    basicVertexArray->bindAttribute(shader, blitz::hashString("pos"));
    basicVertexArray->enableAttribute(shader, blitz::hashString("pos"));

    basicVertexArray->bindAttribute(shader, blitz::hashString("texCoords"));
    basicVertexArray->enableAttribute(shader, blitz::hashString("texCoords"));

    blitz::RenderState* renderState = new blitz::RenderState{ { 0.5f, 0.0f, 0.5f, 1.0f },
                                                              { 0, 0, 400, 500 },
                                                              blitz::Projection::ORTHOGRAPHIC,
                                                              false,
                                                              false,
                                                              shader,
                                                              nullptr,
                                                              true };

    char textureLocation[] = "container.jpg";
    blitz::STBImage2DTextureLoader textureLoader({ nullptr, textureLocation });
    blitz::Texture* tex = textureLoader.load();
	
    bool shouldUseTextureForFirstTriangle = true;
    blitz::ogl::OpenGLTextureSampler* sampler = new blitz::ogl::OpenGLTextureSampler{ tex };
    
	std::vector<blitz::UniformState*> firstTriangleUniforms;
    firstTriangleUniforms.emplace_back(new blitz::UniformState (blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&shouldUseTextureForFirstTriangle));
    firstTriangleUniforms.emplace_back(new blitz::UniformState (blitz::DataType::SAMPLER2D, blitz::hashString("tex"), (void*)&sampler));
	
    blitz::RenderCommand* drawFirstTriangleCommand = new blitz::RenderCommand{ basicVertexArray,
                                                                               {},
                                                                               firstTriangleUniforms,
                                                                               blitz::DrawMode::NORMAL,
                                                                               blitz::PrimitiveType::TRIANGLES,
                                                                               0,
                                                                               0,
                                                                               3 };

    blitz::Vector3f* triangleColor = new blitz::Vector3f{ 0.f, 1.f, 0.f };
    bool shouldUseTextureForSecondTriangle = false;

    std::vector<blitz::UniformState*> secondTriangleUniforms;
    secondTriangleUniforms.emplace_back(new blitz::UniformState (blitz::DataType::VECTOR3F, blitz::hashString("color"), (void*)triangleColor));
    secondTriangleUniforms.emplace_back(new blitz::UniformState (blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&shouldUseTextureForSecondTriangle));

    blitz::RenderCommand* drawSecondTriangleCommand = new blitz::RenderCommand{ basicVertexArray,
                                                                                {},
                                                                                secondTriangleUniforms,
                                                                                blitz::DrawMode::NORMAL,
                                                                                blitz::PrimitiveType::TRIANGLES,
                                                                                3,
                                                                                0,
                                                                                3 };

    blitz::RenderPass* rectangleRenderPass = new blitz::BasicRenderPass(renderState);
    //rectangleRenderPass->add(drawFirstTriangleCommand);
    //rectangleRenderPass->add(drawSecondTriangleCommand);

	blitz::RefCountedResourceManager<blitz::Texture> texturesManager;
    blitz::RefCountedResourceManager<blitz::Model> modelsManager;

	blitz::AssimpModelLoader assimpModelLoader{
        window->getContext(),
		&texturesManager,
		{ nullptr, "D:\\Projects\\LearnOpenGL\\resources\\objects\\nanosuit\\nanosuit.obj", 0 }
    };

	
    const auto modelID = modelsManager.loadResource(&assimpModelLoader);
    const auto model = modelsManager.getResource(modelID);
    blitz::front::BasicModelRenderer modelRenderer({ model.raw() }); //TODO perhaps ModelRenderer should use the ResourcePtr
    for (const auto comand : modelRenderer.produceCommands())
    {
        rectangleRenderPass->add(comand);
    }
    rectangleRenderPass->finish();
    BLITZ_RENDERER->issue(rectangleRenderPass);
    BLITZ_RENDERER->render(window);

    int x;
    std::cin >> x;

    return 0;
}