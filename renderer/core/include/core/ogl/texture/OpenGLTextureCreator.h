#pragma once

#include <GL/glew.h>
#include <blitzcommon/NonCopyable.h>
#include <core/TextureSpec.h>

namespace blitz
{
    class OpenGLTexture;
    class OpenGLContext;

    class GLTextureCreator : NonCopyable
    {
      public:
        static GLenum toGLTextureType(const TextureType& textureType);

      private:
        friend class OpenGLTexture;
        friend class OpenGLContext;
        friend class OpenGLContext;


        static GLuint create(const TextureSpec& textureSpec);
    };
} // namespace blitz