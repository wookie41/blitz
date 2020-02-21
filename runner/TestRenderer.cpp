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
#include <resources/texture/STBImage2DTextureLoader.h>

char* v = "#version 330 core\n"
          "layout (location = 0) in vec3 pos;\n"
          "layout (location = 1) in vec2 texCoords;\n"
          "out vec2 TexCoords;\n"
          "uniform mat4 _bView;\n"
          "void main()\n"
          "{\n"
          "\n"
          "    TexCoords = texCoords;\n"
          "    gl_Position = _bView * vec4(pos, 1.0);\n"
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
    -0.9f, -0.5f, 0.0f, 0.f, 0.f, // left
    -0.0f, -0.5f, 0.0f, .5f, 1.f, // right
    -0.45f, 0.5f, 0.0f, 1.f, 0.f, // top
    // second triangle
    0.0f, -0.5f, 0.0f, 0.f, 0.f, // left
    0.9f, -0.5f, 0.0f, 0.f, 0.f, // right
    0.45f, 0.5f, 0.0f, 0.f, 0.f, // top
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

        char textureLocation[] = "container.jpg";
        blitz::STBImage2DTextureLoader textureLoader({ nullptr, textureLocation });
        tex = textureLoader.load();

        shouldUseTextureForFirstTriangle = true;
        sampler = new blitz::ogl::OpenGLTextureSampler{ tex };

        triangleColor = new blitz::Vector3f{ 0.f, 1.f, 0.f };
        shouldUseTextureForSecondTriangle = false;
    }

    Shader* TestRenderer::getShader() const { return shader; }

    Renderable* TestRenderer::render()
    {
        blitz::UniformState* firstTriangleTexture =
        new blitz::UniformState{ blitz::DataType::SAMPLER2D, blitz::hashString("tex"), (void*)&sampler };
        blitz::UniformState* firstTriangleTextureFlagUniform =
        new blitz::UniformState{ blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&shouldUseTextureForFirstTriangle };

        std::vector<blitz::UniformState*> firstTriangleUniforms{ firstTriangleTextureFlagUniform, firstTriangleTexture };

        blitz::RenderCommand* drawFirstTriangleCommand = new blitz::RenderCommand{ basicVertexArray,
                                                                                   {},
                                                                                   firstTriangleUniforms,
                                                                                   blitz::DrawMode::NORMAL,
                                                                                   blitz::PrimitiveType::TRIANGLES,
                                                                                   0,
                                                                                   0,
                                                                                   3,
                                                                                   0 };

        blitz::UniformState* triangleColorUniform =
        new blitz::UniformState{ blitz::DataType::VECTOR3F, blitz::hashString("color"), (void*)triangleColor };
        blitz::UniformState* textureFlagUniform =
        new blitz::UniformState{ blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&shouldUseTextureForSecondTriangle };

        std::vector<blitz::UniformState*> secondTriangleUniforms = { textureFlagUniform, triangleColorUniform };

        blitz::RenderCommand* drawSecondTriangleCommand = new blitz::RenderCommand{ basicVertexArray,
                                                                                    {},
                                                                                    secondTriangleUniforms,
                                                                                    blitz::DrawMode::NORMAL,
                                                                                    blitz::PrimitiveType::TRIANGLES,
                                                                                    3,
                                                                                    3,
                                                                                    3,
                                                                                    0 };

        return new Renderable{ { drawFirstTriangleCommand, drawSecondTriangleCommand } };
    }

} // namespace blitz::front