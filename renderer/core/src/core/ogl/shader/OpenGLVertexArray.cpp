#include <core/ogl/OpenGLContext.h>
#include <core/ogl/shader/OpenGLVertexArray.h>

#include <core/RendererErrorCode.h>
#include <core/Shader.h>
#include <core/ogl/buffer/OpenGLBuffer.h>

namespace blitz::ogl
{
    OpenGLVertexArray::OpenGLVertexArray(const uint8& numAttributes, const GLuint& vao, OpenGLContext* openGLContext)
    : VertexArray::VertexArray(numAttributes), vaoIdx(vao), openGLContext(openGLContext)
    {
    }

    inline void bindIntAttribute(GLuint index, const VertexAttributeDef& def, GLenum type)
    {
        glVertexAttribIPointer(index, def.size, type, def.stride, (void*)def.offset);
    }

    inline void bindFloatAttribute(GLuint index, const VertexAttributeDef& def, GLenum type)
    {
        glVertexAttribPointer(index, def.size, type, def.normalize, def.stride, (void*)def.offset);
    }

    inline void bindDoubleAttribute(GLuint index, const VertexAttributeDef& def)
    {
        glVertexAttribLPointer(index, def.size, GL_DOUBLE, def.stride, (void*)def.offset);
    }

    void OpenGLVertexArray::bindElementBuffer(Buffer* buffer, const DataType& indicesType)
    {
        bind();
        elementBuffer = buffer;
        this->indicesType = indicesType;
        buffer->bind({0, buffer->getSizeInBytes(), 0, BufferBindTarget::ELEMENT});
        unbind();
    }

    void OpenGLVertexArray::bind() { glBindVertexArray(vaoIdx); }

    void OpenGLVertexArray::unbind() { glBindVertexArray(0); }

    void OpenGLVertexArray::setupAttributes()
    {
        GLint shaderID;
        glGetIntegerv(GL_CURRENT_PROGRAM, &shaderID);
        assert(shaderID > 0);

        for (uint8 attributeIdx = 0; attributeIdx < attributesCount; ++attributeIdx)
        {
            const VertexAttributeDef& attribute = attributes[attributeIdx];
            GLint attributeID = glGetAttribLocation(shaderID, attribute.name);
            assert(attributeIdx != -1);

            // if the buffer is shared among attributes, skip it
            attribute.buffer->bind({0, attribute.buffer->getSizeInBytes(), 0, BufferBindTarget::VERTEX});

            switch (attribute.dataType)
            {
            case DataType::INT:
                bindIntAttribute(attributeID, attribute, GL_INT);
                break;
            case DataType::UINT:
                bindIntAttribute(attributeID, attribute, GL_UNSIGNED_INT);
                break;
            case DataType::FLOAT:
                bindFloatAttribute(attributeID, attribute, GL_FLOAT);
                break;
            case DataType::DOUBLE:
                bindDoubleAttribute(attributeID, attribute);
                break;
            }

            glVertexAttribDivisor(attributeID, static_cast<GLuint>(attribute.updateDivisor));
            glEnableVertexAttribArray(attributeID);
        }
    }

    OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &vaoIdx); }

} // namespace blitz::ogl
