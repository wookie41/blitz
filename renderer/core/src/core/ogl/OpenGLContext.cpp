#include "loguru.hpp"
#include "GL/glew.h"

#include "core/RendererErrorCode.h"
#include "core/ogl/OpenGLBufferFiller.h"
#include "core/ogl/SimpleOpenGLBuffer.h"
#include "core/ogl/OpenGLContext.h"

namespace blitz
{
    OpenGLContext::OpenGLContext() : Context()
    {
        targetsMapping = { { BufferBindTarget::VERTEX, GL_ARRAY_BUFFER },
                           { BufferBindTarget::ELEMENT, GL_ELEMENT_ARRAY_BUFFER } };

        bufferFiller = new OpenGLBufferFiller(this);
    }

    ContextLock OpenGLContext::bindBuffers(std::vector<BufferBinding>& bindings)
    {
        auto contextLock = std::unique_lock(contextMutex);

        for (auto& binding : bindings)
        {
            auto glBufferToBind = dynamic_cast<OpenGLBuffer*>(binding.buffer);
            if (glBufferToBind == nullptr)
            {
                exit(RendererErrorCode::OPENGL_UNSUPPORTED_BUFFER);
            }

            const auto targetIt = targetsMapping.find(binding.target);
            if (targetIt == targetsMapping.end())
            {
                DLOG_F(ERROR, "[OpenGL] Unknown buffer target: %d", binding.target);
                exit(OPENGL_UNKNWON_BUFFER_TARGET);
            }

            const auto target = (*targetIt).second;
            DLOG_F(INFO, "[OpenGL] Binding buffer %d to target %d", glBufferToBind->getId(), target);
            glBindBuffer(target, glBufferToBind->getId());
        }


        return std::move(contextLock);
    }

    OpenGLContext::~OpenGLContext() { delete (bufferFiller); }

    Buffer* OpenGLContext::createBuffer(BufferSpec bufferSpec)
    {
        if (bufferSpec.multiBuffersCount > 0)
        {
            exit(RendererErrorCode::OPENGL_MULTI_BUFFERING_NO_SUPPORRTED);
        }

        auto selfLock = std::lock_guard(selfMutex);

        GLuint bufferId;
        glGenBuffers(1, &bufferId);

        DLOG_F(INFO, "[OpenGL] Buffer with id %d created", bufferId);
        return new SimpleOpenGLBuffer(bufferId, bufferSpec.usageHint);
    }

    const BufferFiller* OpenGLContext::getBufferFiller() { return bufferFiller; }


} // namespace blitz