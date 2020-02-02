#include <core/ogl/OpenGLDevice.h>
#include <core/ogl/framebuffer/OpenGLRenderBufferAttachment.h>
#include <core/ogl/framebuffer/OpenGLTextureAttachment.h>
#include <core/ogl/shader/OpenGLShaderFactory.h>
#include <core/ogl/texture/OpenGLSyncReadTexture.h>
#include <core/ogl/texture/OpenGLSyncReadWriteTexture.h>
#include <core/ogl/texture/OpenGLSyncWriteTexture.h>
#include <core/ogl/texture/OpenGLTextureCreator.h>
#include <core/ogl/texture/OpenGLTextureSampler.h>

namespace blitz::ogl
{

#ifndef NDEBUG
    void setupGLErrorHandler();
#endif

    OpenGLDevice::OpenGLDevice()
    {
        shaderFactory = new OpenGLShaderFactory();
#ifndef NDEBUG
        setupGLErrorHandler();
#endif
    }

    OpenGLDevice::~OpenGLDevice() { delete shaderFactory; }

    Shader* OpenGLDevice::createShader(const ShaderSource& shaderSource) const
    {
        return shaderFactory->createShader(shaderSource);
    }

    Texture* OpenGLDevice::createTexture(const TextureSpec& textureSpec) const
    {
        const auto& textureID = OpenGLTextureCreator::createGLTexture(textureSpec);

        if (textureSpec.isReadable && !textureSpec.isWriteable)
        {
            return new OpenGLSyncReadTexture(textureID, textureSpec);
        }

        if (!textureSpec.isReadable && textureSpec.isWriteable)
        {
            return new OpenGLSyncWriteTexture(textureID, textureSpec);
        }

        return new OpenGLSyncReadWriteTexture(textureID, textureSpec);
    }

    FramebufferAttachment* OpenGLDevice::createFramebufferAttachment(const FramebufferAttachmentSpec& attachmentSpec) const
    {

        GLenum attachmentType;
        switch (attachmentSpec.type)
        {
            case FramebufferAttachmentType::RGB:
            case FramebufferAttachmentType::RGBA:
                attachmentType = GL_COLOR_ATTACHMENT0;
                break;
            case FramebufferAttachmentType::DEPTH:
                attachmentType = GL_DEPTH_ATTACHMENT;
                break;
            case FramebufferAttachmentType::STENCIL:
                attachmentType = GL_STENCIL_ATTACHMENT;
                break;
            case FramebufferAttachmentType::DEPTH_STENCIL:
                attachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
                break;
        }

        if (attachmentSpec.texture != nullptr)
        {
            return createAttachmentUsingUserTexture(attachmentSpec.texture, attachmentType);
        }

        if (attachmentSpec.readable)
        {
            return createTextureBasedAttachment(attachmentSpec);
        }

        return createRenderBufferAttachment(attachmentSpec, attachmentType);
    }

    FramebufferAttachment* OpenGLDevice::createAttachmentUsingUserTexture(Texture* userTexture, const GLenum& type) const
    {
        auto glTexture = dynamic_cast<OpenGLTexture*>(userTexture);
        if (glTexture == nullptr)
            return nullptr;
        return new OpenGLTextureAttachment(glTexture, type, false);
    }

    FramebufferAttachment* OpenGLDevice::createTextureBasedAttachment(const FramebufferAttachmentSpec& attachmentSpec) const
    {
        TextureType textureType;
        switch (attachmentSpec.numberOfDimensions)
        {
            case 1:
                textureType = TextureType::ONE_DIMENSIONAL;
                break;
            case 2:
                textureType = TextureType::TWO_DIMENSIONAL;
                break;
            case 3:
                textureType = TextureType::THREE_DIMENSIONAL;
                break;
            default:
                return {};
        }

        DataType dataType;
        TextureFormat textureFormat;

        switch (attachmentSpec.type)
        {
            case FramebufferAttachmentType::RGB:
                textureFormat = TextureFormat::RGB;
                dataType = DataType::UBYTE;
                break;
            case FramebufferAttachmentType::RGBA:
                textureFormat = TextureFormat::RGBA;
                dataType = DataType::UBYTE;
                break;
            case FramebufferAttachmentType::STENCIL:
                textureFormat = TextureFormat::STENCIL;
                dataType = DataType::FLOAT;
                break;
            case FramebufferAttachmentType::DEPTH:
                textureFormat = TextureFormat::DEPTH;
                dataType = DataType::FLOAT;

                break;
            case FramebufferAttachmentType::DEPTH_STENCIL:
                textureFormat = TextureFormat::DEPTH_STENCIL;
                dataType = DataType::FLOAT;
                break;
        }

        TextureSpec textureSpec{ textureType, attachmentSpec.dimensions, 0,     textureFormat, dataType,
                                 false,       attachmentSpec.readable,   false, nullptr };

        const auto glTexture = dynamic_cast<OpenGLTexture*>(createTexture(textureSpec));

        return new OpenGLTextureAttachment(glTexture, GL_COLOR_ATTACHMENT0, true);
    }

    FramebufferAttachment*
    OpenGLDevice::createRenderBufferAttachment(const FramebufferAttachmentSpec& attachmentSpec, const GLenum& type) const
    {
        if (attachmentSpec.dimensions.x > GL_MAX_RENDERBUFFER_SIZE || attachmentSpec.dimensions.y > GL_MAX_RENDERBUFFER_SIZE)
            return nullptr;

        GLenum internalFormat;

        switch (type)
        {
            case GL_DEPTH_ATTACHMENT:
                internalFormat = GL_DEPTH_COMPONENT32F;
                break;
            case GL_STENCIL_ATTACHMENT:
                internalFormat = GL_STENCIL_INDEX8;
                break;
            case GL_DEPTH_STENCIL_ATTACHMENT:
                internalFormat = GL_DEPTH24_STENCIL8;
                break;
            default:
                return nullptr;
        }

        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, attachmentSpec.dimensions.x, attachmentSpec.dimensions.y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        return new OpenGLRenderBufferAttachment(rbo, type);
    }

    TextureSampler *OpenGLDevice::createSampler(Texture *texture) const
    {
        new blitz::ogl::OpenGLTextureSampler{ texture };
    }


    void GLAPIENTRY glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
#ifndef NDEBUG

        DLOG_F(INFO, "[OpenGL] Debug message: %s type = 0x%x, severity = 0x%x, message = %s\n",
               (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
        #endif
    }

    void setupGLErrorHandler()
    {
#ifndef NDEBUG
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        if ((major == 4 && minor < 2) || major < 4)
        {
            DLOG_F(INFO, "[OpenGL] glDebugMessageCallback is not supported for version %d.%d", major, minor);
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(glMessageCallback, 0);
#endif
    }


} // namespace blitz::ogl