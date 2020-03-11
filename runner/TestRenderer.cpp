#include <TestRenderer.h>

#include <core/Device.h>
#include <core/Logger.h>
#include <core/Renderer.h>

#include <core/Shader.h>
#include <core/ShaderSource.h>
#include <core/VertexArray.h>

#include <core/RenderCommand.h>
#include <core/Window.h>
#include <core/ogl/texture/OpenGLTextureSampler.h>
#include <core/ogl/uniforms/OpenGLSamplerUniformVariable.h>
#include <iostream>
#include <resources/model/Model.h>
#include <resources/model/ModelLoader.h>
#include <resources/texture/TextureLoader.h>


char* v = "#version 330 core\n"
          "layout (location = 0) in vec3 position;\n"
          "layout (location = 2) in vec2 textureCoords;\n"
          "out vec2 TexCoords;\n"
          "uniform mat4 _bView;\n"
          "uniform mat4 _bProjection;\n"
          "void main()\n"
          "{\n"
          "\n"
          "    mat4 model = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));\n"
          "    TexCoords = textureCoords;\n"
          "    gl_Position = _bProjection * _bView * model * vec4(position, 1.0);\n"
          "}";

// char* v = "#version 330 core\n"
//           "layout (location = 0) in vec3 position;\n"
//           "layout (location = 1) in vec2 textureCoords;\n"
//           "out vec2 TexCoords;\n"
//           "void main()\n"
//           "{\n"
//           "\n"
//           "    TexCoords = textureCoords;\n"
//           "    gl_Position = vec4(position, 1.0);\n"
//           "}";


char* f = "#version 330 core\n"
          "layout (location = 0) out vec4 FragColor;  \n"
          "\n"
          "in vec2 TexCoords;"
          "uniform vec3 color;\n"
          "uniform sampler2D diffuseMap;\n"
          "uniform bool useTexture;\n"
          "void main()\n"
          "{\n"
          "if (useTexture)\n"
          "{\n"
          " FragColor = texture(diffuseMap, TexCoords);\n"
          "}\n"
          "else"
          "{\n"
          " FragColor = vec4(color, 1.f);\n"
          "}\n"
          "}";

static float vertexData[] = {
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
};

extern blitz::Device* BLITZ_DEVICE;
extern blitz::Renderer* BLITZ_RENDERER;

namespace blitz::front
{
    TestRenderer::TestRenderer(Window* window, Camera* camera, const ViewPort& viewPort)
    {
        auto vertexBuffer = window->getContext().createBuffer(
        { sizeof(vertexData), blitz::UsageHint::STATIC, blitz::BindHint::VERTEX, vertexData, false, true });

        basicVertexArray = window->getContext().createVertexArray(2);

        basicVertexArray->addAttribute(
        { vertexBuffer, copyStr("position"), blitz::DataType::FLOAT, 3, false, 5 * sizeof(float), 0, 0 });
        basicVertexArray->addAttribute({ vertexBuffer, copyStr("textureCoords"), blitz::DataType::FLOAT, 2, false,
                                         5 * sizeof(float), 3 * sizeof(float), 0 });

        blitz::ShaderSource shaderSource = { blitz::string(copyStr("myshader")), v, nullptr, f };
        shader = BLITZ_DEVICE->createShader(shaderSource);

        char textureLocation[] = "container.jpg";
        tex = textureLoader.loadTexture({ nullptr, textureLocation });

        shouldUseTexture = true;
        sampler = new blitz::ogl::OpenGLTextureSampler{ tex };

        cubeUniforms = new Array<UniformState>(2);
        cubeUniforms->add({ blitz::DataType::SAMPLER2D, blitz::hashString("diffuseMap"), (void*)&sampler });
        cubeUniforms->add({ blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&shouldUseTexture });

        renderCubeCommands = new Array<RenderCommand>(1);
        renderCubeCommands->add(
        { basicVertexArray, {}, cubeUniforms, blitz::DrawMode::NORMAL, blitz::PrimitiveType::TRIANGLE_STRIP, 0, 0, 4, 0 });
        modelLoader = new ModelLoader(window->getContext(), &textureLoader);
        rockModel = modelLoader->load({ nullptr, "D:\\Projects\\LearnOpenGL\\resources\\objects\\rock\\rock.obj" });

        Array<RenderCommand>* modelRenderCommands = modelRenderer.makeRenderable(rockModel);

        testRenderList = new RenderList();
        testRenderList->camera = camera;
        testRenderList->framebuffer = window->getFramebuffer();
        testRenderList->geometry = modelRenderCommands;
        testRenderList->viewPort.x = viewPort.x;
        testRenderList->viewPort.y = viewPort.y;
        testRenderList->viewPort.width = viewPort.width;
        testRenderList->viewPort.height = viewPort.height;
        testRenderList->viewPort.near = viewPort.near;
        testRenderList->viewPort.far = viewPort.far;
    }

    Shader* TestRenderer::getShader() const { return shader; }

    RenderList* TestRenderer::getTestRenderList() { return testRenderList; }
} // namespace blitz::front