#include <core/Device.h>
#include <core/sdl2/SDL2Device.h>
#include <core/ogl/BasicOpenGLRenderer.h>

const blitz::Device* BLITZ_DEVICE = new blitz::SDL2Device();
const blitz::Renderer* BLITZ_RENDERER = new blitz::ogl::BasicOpenGLRenderer();
#ifndef LOGURU_IMPLEMENTATION
	#define LOGURU_IMPLEMENTATION 1
#endif