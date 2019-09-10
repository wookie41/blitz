#include <core/ogl/OpenGLContext.h>
#include <core/ogl/OpenGLVertexArray.h>
#include <loguru.hpp>


namespace blitz
{
    void bindBuffer(GLuint vaoIdx, Buffer* buffer, const BufferBindTarget& target)
    {
        DLOG_F(ERROR, "[OpenGL] Binding VAO: %d", vaoIdx);
        glBindVertexArray(vaoIdx);
        DLOG_F(ERROR, "[OpenGL] Binding target %d to VAO", target);
        buffer->bind(target);
        DLOG_F(ERROR, "[OpenGL] Buffer bound, unbinding VAO");
        glBindVertexArray(0);
    }

    OpenGLVertexArray::OpenGLVertexArray(GLuint vaoIdx, OpenGLContext* openGLContext)
    : vaoIdx(vaoIdx), openGLContext(openGLContext)
    {
    }

    void bindIntAttribute(const VertexAttributeDef& def, GLenum type)
    {
        glVertexAttribIPointer(def.index, def.size, type, def.stride, (void*)def.offset);
    }

    void bindFloatAttribute(const VertexAttributeDef& def, GLenum type)
    {
        glVertexAttribPointer(def.index, def.size, type, def.stride, (void*)def.offset);
    }

    void bindDoubleAttribute(const VertexAttributeDef& def)
    {
        glVertexAttribLPointer(def.index, def.size, GL_DOUBLE, def.stride, (void*)def.offset);
    }

    void OpenGLVertexArray::bindVertexBuffer(Buffer* buffer)
    {
        vertexBuffer = buffer;
        openGLContext->run([this](Context* context) { bindBuffer(vaoIdx, vertexBuffer, BufferBindTarget::VERTEX); });
    }

    void OpenGLVertexArray::bindElementBuffer(Buffer* buffer)
    {
        elementBuffer = buffer;
        openGLContext->run([this](Context* context) { bindBuffer(vaoIdx, elementBuffer, BufferBindTarget::ELEMENT); });
    }

    void OpenGLVertexArray::setVertexAttribute(const VertexAttributeDef& vertexAttributeDef)
    {
        openGLContext->run([this, &vertexAttributeDef](Context* context) {
            glBindVertexArray(this->vaoIdx);

            switch (vertexAttributeDef.dataType)
            {
            case DataType::INT_32:
                bindIntAttribute(vertexAttributeDef, GL_INT);
                break;
            case DataType::UINT_32:
                bindIntAttribute(vertexAttributeDef, GL_UNSIGNED_INT);
                break;
            case DataType::FLOAT:
                bindFloatAttribute(vertexAttributeDef, GL_FLOAT);
                break;
            case DataType::DOUBLE:
                bindDoubleAttribute(vertexAttributeDef);
                break;
            }

            glBindVertexArray(0);
        });
    }

    void OpenGLVertexArray::bind() { glBindVertexArray(vaoIdx); }

    void OpenGLVertexArray::unbind() { glBindVertexArray(0); }


    OpenGLVertexArray::~OpenGLVertexArray()
    {
        if (vertexBuffer != nullptr)
        {
            delete vertexBuffer;
        }
        if (elementBuffer != nullptr)
        {
            delete elementBuffer;
        }
        glDeleteVertexArrays(1, &vaoIdx);
    }
} // namespace blitz
