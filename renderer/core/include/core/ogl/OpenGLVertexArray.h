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

        void setVertexAttribute(const VertexAttributeDef& vertexAttributeDef) override;

        ~OpenGLVertexArray() override;

      private:
        explicit OpenGLVertexArray(GLuint vaoIdx, OpenGLContext* openGLContext);

        GLuint vaoIdx;
        OpenGLContext* openGLContext;
    };
} // namespace blitz