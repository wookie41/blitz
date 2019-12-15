#include <core/Device.h>
#include <core/Logger.h>

#include <core/Shader.h>
#include <core/ShaderSource.h>
#include <core/VertexArray.h>

#include "core/RenderCommand.h"
#include "core/RenderState.h"
#include <core/BasicRenderPass.h>
#include <core/Renderer.h>
#include <iostream>
#include <core/Window.h>

char* v = "#version 330 core\n"
          "layout (location = 0) in vec3 pos;"
          "  \n"
          "void main()\n"
          "{\n"
          "\n"
          "    gl_Position = vec4(pos, 1.0);\n"
          "}";


char* f = "#version 330 core\n"
          "layout (location = 0) out vec4 FragColor;  \n"
          "\n"
          "uniform vec3 color;\n"
          "void main()\n"
          "{\n"
          "    FragColor = vec4(color, 1.f);\n"
          "}";

extern blitz::Device* BLITZ_DEVICE;
extern blitz::Renderer* BLITZ_RENDERER;

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);
    auto windowDef = blitz::WindowDef{ 0, 0, 400, 400, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    window->show();
    float vertexData[] = {
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, // top
        // second triangle
        0.0f, -0.5f, 0.0f, // left
        0.9f, -0.5f, 0.0f, // right
        0.45f, 0.5f, 0.0f // top
    };
    auto vertexBuffer = window->getContext().createBuffer(
    { sizeof(vertexData), blitz::UsageHint::STATIC, 0, blitz::BindHint::VERTEX, vertexData, false, true });

    blitz::VertexArray* basicVertexArray = window->getContext().createVertexArray();
    basicVertexArray->addAttribute({ vertexBuffer, "pos", blitz::DataType::FLOAT, 3, false, 3 * sizeof(float), 0, 0 });

    blitz::ShaderSource shaderSource = { "myshader", v, nullptr, f };
    blitz::Shader* shader = BLITZ_DEVICE->createShader(shaderSource);

    basicVertexArray->bindAttribute(shader, blitz::hashString("pos"));
    basicVertexArray->enableAttribute(shader, blitz::hashString("pos"));

    blitz::RenderState* renderState = new blitz::RenderState{ { 0.5f, 0.0f, 0.5f, 1.0f },
                                                              { 0, 0, 400, 500 },
                                                              blitz::Projection::ORTHOGRAPHIC,
                                                              false,
                                                              false,
                                                              shader,
                                                              nullptr,
                                                              true };

    blitz::Vector3f* col = new blitz::Vector3f{ 1.f, 0.f, 0.f };
    blitz::UniformState* colorUniform =
    new blitz::UniformState{ blitz::UniformState{ blitz::DataType::VECTOR3F, blitz::hashString("color"), (void*)col } };
    blitz::ListNode<blitz::UniformState>* states = new blitz::ListNode<blitz::UniformState>{ colorUniform, nullptr };

    blitz::RenderCommand* renderCommand = new blitz::RenderCommand{
        basicVertexArray, nullptr, states, blitz::DrawMode::NORMAL, blitz::PrimitiveType::TRIANGLES, 0, 3, 0
    };

    blitz::Vector3f* col1 = new blitz::Vector3f{ 0.f, 1.f, 0.f };
    blitz::UniformState* colorUniform1 =
    new blitz::UniformState{ blitz::UniformState{ blitz::DataType::VECTOR3F, blitz::hashString("color"), (void*)col1 } };
    blitz::ListNode<blitz::UniformState>* states1 = new blitz::ListNode<blitz::UniformState>{ colorUniform1, nullptr };

    blitz::RenderCommand* renderCommand2 = new blitz::RenderCommand{
        basicVertexArray, nullptr, states1, blitz::DrawMode::NORMAL, blitz::PrimitiveType::TRIANGLES, 3, 3, 0
    };

    blitz::RenderPass* renderPass = new blitz::BasicRenderPass(renderState);
    renderPass->add(renderCommand);
    renderPass->add(renderCommand2);
    renderPass->finish();

    BLITZ_RENDERER->issue(renderPass);
    BLITZ_RENDERER->render(window);

    int x;
    std::cin >> x;

    return 0;
}