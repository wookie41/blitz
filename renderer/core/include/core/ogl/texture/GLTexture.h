#pragma once

#include <GL/glew.h>
#include <core/Texture.h>

namespace blitz
{
    class GLTexture : Texture
    {
        virtual void upload(void *data, size_t length) override;
        virtual void *download(void *destination) override;
        virtual bool isReadyToRead() const override;

        void bind() override;

    protected:
        GLTexture(GLuint textureID, const TextureSpec& textureSpec);

        GLuint textureID;
    };

} // namespace blitz