#pragma once

#include <GL/glew.h>
#include <blitzcommon/NonCopyable.h>
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

        static GLuint create(const TextureSpec& textureSpec);
    };
} // namespace blitz::ogl