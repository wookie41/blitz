#pragma once

#include <core/Precompiled.h>
#include <core/ogl/texture/OpenGLSyncReadTexture.h>
#include <core/ogl/texture/OpenGLSyncWriteTexture.h>

namespace blitz::ogl
{
    class OpenGLSyncReadWriteTexture: public OpenGLTexture
    {
        friend class OpenGLDevice;

    public:
        OpenGLSyncReadWriteTexture(OpenGLSyncReadWriteTexture&& rhs) = default;
        OpenGLSyncReadWriteTexture(const OpenGLSyncReadWriteTexture& rhs) = default;
        OpenGLSyncReadWriteTexture& operator=(const OpenGLSyncReadWriteTexture& rhs) = default;
        OpenGLSyncReadWriteTexture& operator=(OpenGLSyncReadWriteTexture&& rhs) = default;

        void upload(void *data) override;
        void upload(void *data, const Range3 &range) override;

        void *download(void *destination, uint8 mipmapLevel) override;
        void *download(void *destination, uint8 mipmapLevel, const Range3 &range) override;

        bool isReadyToRead() const override;

        virtual ~OpenGLSyncReadWriteTexture();

    private:
        OpenGLSyncReadTexture readInterface;
        OpenGLSyncWriteTexture writeInterface;
        OpenGLSyncReadWriteTexture(const GLuint& texID, const TextureSpec& texSpec);
    };
} // namespace blitz::ogl