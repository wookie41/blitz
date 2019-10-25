#include <blitzcommon/HashUtils.h>
#include <core/Context.h>
#include <core/RendererErrorCode.h>
#include <core/ogl/buffer/OpenGLBuffer.h>
#include <loguru.hpp>
#include <unordered_map>

namespace blitz::ogl
{
    static std::unordered_map<BufferBindTarget, GLenum , EnumClassHash> targetsMapping = {
        { BufferBindTarget::VERTEX, GL_ARRAY_BUFFER },
        { BufferBindTarget::ELEMENT, GL_ELEMENT_ARRAY_BUFFER },
        { BufferBindTarget::WRITE, GL_COPY_WRITE_BUFFER }
    };

    OpenGLBuffer::OpenGLBuffer(const GLuint& id, const UsageHint& usageHint) : Buffer(usageHint), glBufferID(id) {}

    GLuint OpenGLBuffer::getId() const { return glBufferID; }

    OpenGLBuffer::~OpenGLBuffer()
    {
        DLOG_F(INFO, "[OpenGL] Deleting buffer with id %d", glBufferID);
        glDeleteBuffers(1, &glBufferID);
    }

    void OpenGLBuffer::bind(const BufferBindTarget& bindTarget)
    {
        const auto targetIt = targetsMapping.find(bindTarget);
        if (targetIt == targetsMapping.end())
        {
            DLOG_F(ERROR, "[OpenGL] Unknown buffer target: %d", bindTarget);
            exit(OPENGL_UNKNWON_BUFFER_TARGET);
        }

        auto glTarget = (*targetIt).second;
        DLOG_F(INFO, "[OpenGL] Binding buffer %d to target %d", glBufferID, glTarget);
        glBindBuffer(glTarget, glBufferID);
    }
} // namespace blitz::ogl