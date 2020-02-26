#include <TestRenderer.h>
#include <front/Renderable.h>

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
#include <resources/texture/TextureLoader.h>

char* v = "#version 330 core\n"
          "layout (location = 0) in vec3 pos;\n"
          "layout (location = 1) in vec2 texCoords;\n"
          "out vec2 TexCoords;\n"
          "uniform mat4 _bView;\n"
          "uniform mat4 _bProjection;\n"
          "void main()\n"
          "{\n"
          "\n"
          "    mat4 model = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));\n"
          "    TexCoords = texCoords;\n"
          "    gl_Position = _bProjection * _bView * model* vec4(pos, 1.0);\n"
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

static float vertexData[] = {
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
};

extern blitz::Device* BLITZ_DEVICE;
extern blitz::Renderer* BLITZ_RENDERER;

namespace blitz::front
{
    TestRenderer::TestRenderer(Window* window)
    {
        auto vertexBuffer = window->getContext().createBuffer(
        { sizeof(vertexData), blitz::UsageHint::STATIC, 0, blitz::BindHint::VERTEX, vertexData, false, true });

        basicVertexArray = window->getContext().createVertexArray();

        basicVertexArray->addAttribute({ vertexBuffer, "pos", blitz::DataType::FLOAT, 3, false, 5 * sizeof(float), 0, 0 });
        basicVertexArray->addAttribute(
        { vertexBuffer, "texCoords", blitz::DataType::FLOAT, 2, false, 5 * sizeof(float), 3 * sizeof(float), 0 });

        blitz::ShaderSource shaderSource = { "myshader", v, nullptr, f };
        shader = BLITZ_DEVICE->createShader(shaderSource);

        basicVertexArray->bindAttribute(shader, blitz::hashString("pos"));
        basicVertexArray->enableAttribute(shader, blitz::hashString("pos"));

        basicVertexArray->bindAttribute(shader, blitz::hashString("texCoords"));
        basicVertexArray->enableAttribute(shader, blitz::hashString("texCoords"));

        TextureLoader textureLoader;
        char textureLocation[] = "container.jpg";
        tex = textureLoader.loadTexture({ nullptr, textureLocation });

        shouldUseTexture = true;
        sampler = new blitz::ogl::OpenGLTextureSampler{ tex };
    }

    Shader* TestRenderer::getShader() const { return shader; }

    Renderable* TestRenderer::getTestRenderable()
    {
        blitz::UniformState* textureUniformState =
        new blitz::UniformState{ blitz::DataType::SAMPLER2D, blitz::hashString("tex"), (void*)&sampler };
        blitz::UniformState* textureFlagUniformState =
        new blitz::UniformState{ blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&shouldUseTexture };

        std::vector<blitz::UniformState*> uniforms{ textureUniformState, textureFlagUniformState };

        blitz::RenderCommand* drawCubeCommand = new blitz::RenderCommand{
            basicVertexArray, {}, uniforms, blitz::DrawMode::NORMAL, blitz::PrimitiveType::TRIANGLE_STRIP, 0, 0, 4, 0
        };


        return new Renderable{ { drawCubeCommand } };
    }

} // namespace blitz::front