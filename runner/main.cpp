#include "core/Device.h"
#include "core/Logger.h"
#include <core/VertexArray.h>

#include <iostream>
#include <vector>

extern const blitz::Device *BLITZ_DEVICE;

int main(int argc, char **argv) {
    blitz::Logger::init(argc, argv);
    auto windowDef = blitz::WindowDef{0, 0, 400, 400, "test"};
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    auto buffer = window->getContext().createBuffer({blitz::UsageHint::STATIC, 0});
    blitz::VertexArray* array = window->getContext().createVertexArray();
    array->bind();
    int x;
    std::cin >> x;
    delete buffer;
    delete array;
    return 0;
}