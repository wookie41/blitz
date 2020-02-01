#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/texture/OpenGLTextureUtils.h>
#include <core/ogl/OpenGLDataType.h>

namespace blitz::ogl
{

    GLuint OpenGLTextureCreator::createGLTexture(const TextureSpec &textureSpec)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);

        const auto glTextureType = toGLTextureType(textureSpec.textureType);
        const auto internalFormat = toGLTextureFormat(textureSpec.textureFormat);
        const auto dataType = mapToGLDataType(textureSpec.dataType);

        glBindTexture(glTextureType, textureID);
    	
        switch (glTextureType)
        {
        case GL_TEXTURE_1D:
            glTexImage1D(GL_TEXTURE_1D, textureSpec.mipmapLevel, internalFormat, textureSpec.dimensions.x, 0,
                         internalFormat, dataType, textureSpec.data);
            break;

        case GL_TEXTURE_2D:
            glTexImage2D(GL_TEXTURE_2D, textureSpec.mipmapLevel, internalFormat, textureSpec.dimensions.x,
                         textureSpec.dimensions.y, 0, internalFormat, dataType, textureSpec.data);
            break;

        case GL_TEXTURE_3D:
            glTexImage3D(GL_TEXTURE_3D, textureSpec.mipmapLevel, internalFormat, textureSpec.dimensions.x,
                         textureSpec.dimensions.y, textureSpec.dimensions.z, 0, internalFormat, dataType, textureSpec.data);
            break;
        }

        glGenerateMipmap(glTextureType);
        glBindTexture(glTextureType, 0);

    	return textureID;
    }
} // namespace blitz::ogl