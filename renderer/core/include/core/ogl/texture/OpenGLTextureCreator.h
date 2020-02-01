#pragma once

#include <core/Precompiled.h>
#include <core/TextureSpec.h>

namespace blitz::ogl
{
    class OpenGLTexture;
    class OpenGLDevice;

    class OpenGLTextureCreator : NonCopyable
    {
      public:

      private:
        friend class OpenGLTexture;
        friend class OpenGLDevice;

        static GLuint createGLTexture(const TextureSpec &textureSpec);
    };
} // namespace blitz::ogl