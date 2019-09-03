#include "core/Device.h"
#include "core/Logger.h"

#include <iostream>
#include <vector>
extern const blitz::Device* BLITZ_DEVICE;

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);
    auto windowDef = blitz::WindowDef {0, 0, 400, 400, "test"};
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    window->hide();
    return 0;
}