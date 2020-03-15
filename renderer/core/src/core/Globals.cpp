#include <core/Device.h>
#include <core/sdl2/SDL2Device.h>
#include <core/ogl/BasicOpenGLRenderer.h>

namespace blitz
{
    Device* BLITZ_DEVICE = new SDL2Device;
    Renderer* BLITZ_RENDERER = new ogl::BasicOpenGLRenderer;
} // namespace blitz