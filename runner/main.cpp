#include "core/Device.h"
#include "core/Logger.h"

#include <core/VertexArray.h>
#include <core/Shader.h>
#include <core/ShaderSource.h>

#include <iostream>
#include <vector>
#include <core/BufferRange.h>

char* v = "#version 430 core\n"
          "layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0\n"
          "layout (location = 1) in vec3 aColor; // the color variable has attribute position 1\n"
          "  \n"
          "layout (std140) uniform Matrices\n"
          "{\n"
          "    mat4 projection;\n"
          "    mat4 view;\n"
          "};\n"
          "uniform int numOfEnemies;\n"
          "layout (std140, binding=0) uniform Matrices2\n"
          "{\n"
          "    mat4 projection2;\n"
          "    mat4 view2;\n"
          "};\n"
          "uniform mat4 model;"
          "out vec3 ourColor; // output a color to the fragment shader\n"
          "\n"


          "void main()\n"
          "{\n"
          "    gl_Position = vec4(aPos, 1.0 + numOfEnemies);\n"
          "    ourColor = aColor; // set ourColor to the input color we got from the vertex data\n"
          "}";


char* f = "#version 430 core\n"
          "layout (location = 3) out vec4 FragColor;  \n"
          "in vec3 ourColor;\n"
          "uniform sampler2D tex;\n"
          "  \n"
          "void main()\n"
          "{\n"
          "    FragColor = vec4(ourColor, 1.0) +  texture(tex, vec2(1, 1));\n"
          "}";

extern const blitz::Device* BLITZ_DEVICE;

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);
    auto windowDef = blitz::WindowDef{ 0, 0, 400, 400, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);

    char* dupa = "xdxd";
    auto buffer = window->getContext().createBuffer({4, blitz::UsageHint::STATIC, 0, blitz::BindHint::INDEX, dupa, true, true});
    auto buffer1 = window->getContext().createBuffer({4, blitz::UsageHint::STATIC, 0, blitz::BindHint::INDEX, dupa, true, true});
    auto buffer2 = window->getContext().createBuffer({4, blitz::UsageHint::STATIC, 0, blitz::BindHint::INDEX, dupa, true, true});

    blitz::VertexArray* array = window->getContext().createVertexArray();

    blitz::ShaderSource source = { "myshader",  v, nullptr, f };
    blitz::ShaderSource source2 = { "myshader2",  v, nullptr, f };

    auto shader = BLITZ_DEVICE->createShader(source);
    auto shader1 = BLITZ_DEVICE->createShader(source);
    auto uniform = shader->getUniformVariable<blitz::int32>("numOfEnemies");
    *uniform = 2;
    blitz::BufferRange range {buffer, 0, 0};
    blitz::BufferRange range2 {buffer2, 0, 0};
    shader->bindUniformBlock("Matrices", &range);
    shader->bindUniformBlock("Matrices2", &range);

    shader1->bindUniformBlock("Matrices", &range);
    shader1->bindUniformBlock("Matrices2", &range2);

    shader->attach(array);
    shader->use(nullptr);
    shader1->use(nullptr);
    int x;
    std::cin >> x;

    delete shader;
    delete buffer;
    delete array;
    return 0;
}