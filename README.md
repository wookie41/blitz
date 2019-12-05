# blitz
blitz is (supposed to be) a 3D game engine. It's name comes from the fact, that is supposed to be fast, as the german offensive.

# Installation
blitz has a few 3rd party dependencies, like the 3d math library, or cross-platform window/input layer, which are defined as git submodules.

To install all the above dependencies, run:
```
git submodule update --init --recursive
```

#MSVS

While working in Visual Studio on Windows you also have to point the linker to the place where the glew's and sdl2's libs are located.
To do this, right-click on `runner`, choose `Properties`, the `VC++ Directories`, on the right pick `Library Directories` and add
the location mentioned aboce.

# Coding conventions

### [Core] Renderer

The renderer should be as simple (and as fast) as it can be. It's job is to provide
an abstraction over the underlying OS and graphics API so the same code can draw stuff on Linux, 
Mac and Window (Windows was named last for a reason).

Having this in mind, even tho it's written in C++, it shouldn't make use of any of 
the fancy C++ stuff, like smart pointers and etc.

###### Smart Pointers
No smart pointers usage is allowed in the core of the renderer.
Define ownership using a raw pointer. Whoever creates an object is also responsible
for deleting it.

Only the owner should use the pointer, if there is a need to share the object, just
use a reference.
