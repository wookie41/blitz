#include "core/Device.h"
#include "core/Logger.h"

#include <core/VertexArray.h>
#include <core/Shader.h>
#include <core/ShaderSource.h>

#include <iostream>
#include <vector>

char* v = "#version 330 core\n"
          "layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0\n"
          "layout (location = 1) in vec3 aColor; // the color variable has attribute position 1\n"
          "  \n"
          "out vec3 ourColor; // output a color to the fragment shader\n"
          "\n"
          "void main()\n"
          "{\n"
          "    gl_Position = vec4(aPos, 1.0);\n"
          "    ourColor = aColor; // set ourColor to the input color we got from the vertex data\n"
          "}";


char* f = "#version 330 core\n"
          "out vec4 FragColor;  \n"
          "in vec3 ourColor;\n"
          "uniform int x;\n"
          "  \n"
          "void main()\n"
          "{\n"
          "    FragColor = vec4(ourColor, 1.0 + x);\n"
          "}";

extern const blitz::Device* BLITZ_DEVICE;

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);
    auto windowDef = blitz::WindowDef{ 0, 0, 400, 400, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    auto buffer = window->getContext().createBuffer({ blitz::UsageHint::STATIC, 0 });
    blitz::VertexArray* array = window->getContext().createVertexArray();

    blitz::ShaderSource source = {  v, nullptr, f };
    auto shader = BLITZ_DEVICE->createShader(source);
    auto uniform = shader->getUniformVariable<uint32_t>("x");
    shader->attach(array);
    *uniform = 2;

    shader->use();

    int x;
    std::cin >> x;


    delete shader;
    delete buffer;
    delete array;
    return 0;
}