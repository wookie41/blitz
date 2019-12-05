#include <core/Device.h>
#include <core/sdl2/SDL2Device.h>
#include <core/ogl/BasicOpenGLRenderer.h>

#ifndef LOGURU_IMPLEMENTATION
	#define LOGURU_IMPLEMENTATION 1
#endif

blitz::Device* BLITZ_DEVICE = new blitz::SDL2Device();
blitz::Renderer* BLITZ_RENDERER = new blitz::ogl::BasicOpenGLRenderer();