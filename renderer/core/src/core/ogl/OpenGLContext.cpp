#include "loguru.hpp"

#include "GL/glew.h"
#include "core/ogl/OpenGLContext.h"
#include "core/RendererErrorCode.h"


namespace blitz
{
    OpenGLContext::OpenGLContext() : Context()
    {
        targetsMapping = { { BufferBindTarget::VERTEX, GL_ARRAY_BUFFER },
                                 { BufferBindTarget::ELEMENT, GL_ELEMENT_ARRAY_BUFFER } };
    }

    ContextLock OpenGLContext::bindBuffers(const std::vector<BufferBinding>& bindings)
    {
        auto contextLock = std::unique_lock(contextMutex);

        for (const auto& binding : bindings)
        {
            const auto targetIt = targetsMapping.find(binding.target);
            if (targetIt == targetsMapping.end())
            {
                DLOG_F(ERROR, "Unknown GL buffer target: %d", binding.target);
                exit(OPENGL_UNKNWON_BUFFER_TARGET);
            }

            const auto bufferIt = buffersMapping.find((void*)binding.buffer);
            if (bufferIt == buffersMapping.end())
            {
                DLOG_F(ERROR, "Unknown GL buffer: %d", binding.target);
                exit(OPENGL_UNKNWON_BUFFER);
            }

            const auto target = (*targetIt).second;
            const auto buffer = (*bufferIt).second;
            glBindBuffer(target, buffer);
        }

        return std::move(contextLock);
    }


} // namespace blitz