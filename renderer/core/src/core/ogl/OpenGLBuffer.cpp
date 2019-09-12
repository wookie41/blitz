#include <loguru.hpp>
#include <unordered_map>

#include <blitzcommon/HashUtils.h>
#include <core/Context.h>
#include <core/RendererErrorCode.h>
#include <core/ogl/OpenGLBuffer.h>

namespace blitz
{
    static std::unordered_map<BufferBindTarget, uint16_t, EnumClassHash> targetsMapping = {
        { BufferBindTarget::VERTEX, GL_ARRAY_BUFFER },
        { BufferBindTarget::ELEMENT, GL_ELEMENT_ARRAY_BUFFER }
    };

    OpenGLBuffer::OpenGLBuffer(const GLuint& id, const UsageHint& usageHint) : Buffer(usageHint), id(id) {}

    GLuint OpenGLBuffer::getId() const { return id; }

    OpenGLBuffer::~OpenGLBuffer()
    {
        DLOG_F(INFO, "[OpenGL] Deleting buffer with id %d", id);
        glDeleteBuffers(1, &id);
    }

    void OpenGLBuffer::bind(const BufferBindTarget& bindTarget)
    {
        const auto targetIt = targetsMapping.find(bindTarget);
        if (targetIt == targetsMapping.end())
        {
            DLOG_F(ERROR, "[OpenGL] Unknown buffer target: %d", targetIt);
            exit(OPENGL_UNKNWON_BUFFER_TARGET);
        }

        const auto target = (*targetIt).second;
        DLOG_F(INFO, "[OpenGL] Binding buffer %d to target %d", id, target);
        glBindBuffer(target, id);
    }
} // namespace blitz