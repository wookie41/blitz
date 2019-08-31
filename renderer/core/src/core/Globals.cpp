#include "core/Device.h"
#include "core/sdl2/SDL2Device.h"


// IMPORTANT
// Remember to call init before any other calls to the Device are made
const blitz::Device* BLITZ_DEVICE = new blitz::SDL2Device();