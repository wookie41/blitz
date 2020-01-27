#pragma once

#include <GL/glew.h>
#include <core/VertexArray.h>

namespace blitz::ogl
{
    class OpenGLContext;

    class OpenGLVertexArray : public VertexArray
    {
        friend class OpenGLContext;

      public:

        void bind() override;
        void unbind() override;

        void bindElementBuffer(Buffer* buffer, const DataType& indicesType) override;

        void bindAttribute(Shader* shader, const hash& nameHash) override;

        void enableAttribute(Shader* shader, const hash &nameHash) override;
        void disableAttribute(Shader* shader, const hash &nameHash) override;

        ~OpenGLVertexArray() override;

      private:
        explicit OpenGLVertexArray(GLuint vaoIdx, OpenGLContext* openGLContext);

        GLint queryAttributeLocationByHash(const hash& nameHash) const;

        GLuint vaoIdx;
        OpenGLContext* openGLContext;
    };
} // namespace blitz::ogl