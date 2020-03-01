#pragma once

#include <core/Precompiled.h>
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
        void setupAttributes() override;

        void bindElementBuffer(Buffer* buffer, const DataType& indicesType) override;

        ~OpenGLVertexArray() override;

      protected:
      private:
        explicit OpenGLVertexArray(const uint8& numAttributes, const GLuint& vao, OpenGLContext* openGLContext);

        GLint queryAttributeLocationByHash(const hash& nameHash) const;

        GLuint vaoIdx;
        OpenGLContext* openGLContext;
    };
} // namespace blitz::ogl