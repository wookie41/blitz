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

        void bindElementBuffer(Buffer* buffer, const DataType& indicesType) override;

        ~OpenGLVertexArray() override;

    protected:
    
        void bind() override;
        void unbind() override;
        void bindAttribute(const hash& nameHash) override;
        void enableAttribute(const hash &nameHash) override;
        void disableAttribute(const hash &nameHash) override;

      private:
        explicit OpenGLVertexArray(GLuint vaoIdx, OpenGLContext* openGLContext);

        GLint queryAttributeLocationByHash(const hash& nameHash) const;

        GLuint vaoIdx;
        OpenGLContext* openGLContext;
    };
} // namespace blitz::ogl