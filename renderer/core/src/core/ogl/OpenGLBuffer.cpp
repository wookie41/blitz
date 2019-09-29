#include <core/ogl/OpenGLBuffer.h>
#include <loguru.hpp>
#include <unordered_map>
#include <cstdint>
#include <blitzcommon/HashUtils.h>
#include <core/Context.h>
#include <core/RendererErrorCode.h>

namespace blitz
{
    static std::unordered_map<BindTarget, std::uint16_t, EnumClassHash> targets = { { BindTarget::VERTEX, GL_ARRAY_BUFFER },
                                                                                      { BindTarget::ELEMENT, GL_ELEMENT_ARRAY_BUFFER } };

    static std::unordered_map<IndexedBindTarget, std::uint16_t, EnumClassHash> indexedTargets = { { IndexedBindTarget::UNIFORM_BLOCK, GL_UNIFORM_BUFFER } };

    template <typename T>
    std::uint16_t mapToGLTarget(const T &bindTarget, const std::unordered_map<T, std::uint16_t, EnumClassHash>& mapping)
    {
        const auto targetIt = mapping.find(bindTarget);
        if (targetIt == mapping.end())
        {
            DLOG_F(ERROR, "[OpenGL] Unknown buffer target: %d", bindTarget);
            exit(OPENGL_UNKNWON_BUFFER_TARGET);
        }

        return (*targetIt).second;
    }

    OpenGLBuffer::OpenGLBuffer(const GLuint& id, const UsageHint& usageHint) : Buffer(usageHint), glBufferID(id) {}

    GLuint OpenGLBuffer::getId() const { return glBufferID; }

    OpenGLBuffer::~OpenGLBuffer()
    {
        DLOG_F(INFO, "[OpenGL] Deleting buffer with id %d", glBufferID);
        glDeleteBuffers(1, &glBufferID);
    }

    void OpenGLBuffer::bind(const BindTarget& bindTarget)
    {
        std::uint16_t glTarget = mapToGLTarget<BindTarget>(bindTarget, targets);
        DLOG_F(INFO, "[OpenGL] Binding buffer %d to target %d", glBufferID, glTarget);
        glBindBuffer(glTarget, glBufferID);
    }

    void OpenGLBuffer::bindIndexed(const IndexedBindTarget& bindTarget, uint16_t index)
    {
        std::uint16_t glTarget = mapToGLTarget<IndexedBindTarget>(bindTarget, indexedTargets);
        DLOG_F(INFO, "[OpenGL] Binding buffer %d to indexed target %d, index %d", glBufferID, glTarget, index);
        glBindBufferBase(glTarget, index, glBufferID);
    }

    void OpenGLBuffer::bindIndexedRange(const IndexedBindTarget& bindTarget, uint16_t index, const Range& range)
    {
        std::uint16_t glTarget = mapToGLTarget<IndexedBindTarget>(bindTarget, indexedTargets);
        DLOG_F(INFO, "[OpenGL] Binding buffer %d to indexed target %d, index %d", glBufferID, glTarget, index);
        glBindBufferRange(glTarget, index, glBufferID, range.offset, range.size);
    }
} // namespace blitz