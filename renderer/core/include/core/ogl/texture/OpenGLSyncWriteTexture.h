#pragma once

#include <core/ogl/texture/OpenGLTexture.h>

namespace blitz::ogl
{
    class OpenGLSyncWriteTexture: public OpenGLTexture
    {
        friend class OpenGLDevice;
        friend class OpenGLSyncReadWriteTexture;

    public:
        OpenGLSyncWriteTexture(OpenGLSyncWriteTexture&& rhs) = default;
        OpenGLSyncWriteTexture(const OpenGLSyncWriteTexture& rhs) = default;

        OpenGLSyncWriteTexture& operator=(const OpenGLSyncWriteTexture& rhs) = default;
        OpenGLSyncWriteTexture& operator=(OpenGLSyncWriteTexture&& rhs) = default;

        void upload(void *data) override;
        void upload(void *data, const Range3& range) override;

    protected:

        void writeToTexture(void* data, const Range3& range);

        OpenGLSyncWriteTexture(const GLuint& texID, const TextureSpec& texSpec);
    };
}