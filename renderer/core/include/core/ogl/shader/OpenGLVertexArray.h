#pragma once

#include <GL/glew.h>
#include <core/VertexArray.h>

namespace blitz
{
    class OpenGLContext;

    class OpenGLVertexArray : public VertexArray
    {
        friend class OpenGLContext;

      public:

        void bind() override;
        void unbind() override;

        void bindVertexBuffer(Buffer* buffer) override;
        void bindElementBuffer(Buffer* buffer) override;

        void bindAttribute(const hash& nameHash) override;

        void enable(const hash& nameHash) override;
        void disable(const hash& nameHash) override;

        ~OpenGLVertexArray() override;

      private:
        explicit OpenGLVertexArray(GLuint vaoIdx, OpenGLContext* openGLContext);

        GLuint queryAttributeLocationByHash(const hash& nameHash) const;

        GLuint vaoIdx;
        OpenGLContext* openGLContext;
    };
} // namespace blitz