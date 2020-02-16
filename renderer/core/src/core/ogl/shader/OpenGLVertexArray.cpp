#include <core/ogl/OpenGLContext.h>
#include <core/ogl/shader/OpenGLVertexArray.h>

#include <core/RendererErrorCode.h>
#include <core/Shader.h>
#include <core/ogl/buffer/OpenGLBuffer.h>

namespace blitz::ogl
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

    GLint queryGLShaderID()
    {
        GLint shaderID;
        glGetIntegerv(GL_CURRENT_PROGRAM, &shaderID);
        return shaderID;
    }

    GLuint queryAttributeLocation(const GLint& shaderID, const char* name)
    {
        auto attributeIdx = glGetAttribLocation(shaderID, name);
        assert(attributeIdx != -1);
        return attributeIdx;
    }

    GLint OpenGLVertexArray::queryAttributeLocationByHash(const hash& nameHash) const
    {
        const auto& vertexAttributeDef = getAttribute(nameHash);
        const auto shaderID = queryGLShaderID();
        return queryAttributeLocation(shaderID, vertexAttributeDef.name.c_str());
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
        elementBuffer = buffer;
        this->indicesType = indicesType;
        bindBuffer(vaoIdx, elementBuffer, BufferBindTarget::ELEMENT);
    }

    void OpenGLVertexArray::bind()
    {
        DLOG_F(INFO, "[OpenGL] Binding VAO %d", vaoIdx);
        glBindVertexArray(vaoIdx);
    }

    void OpenGLVertexArray::unbind()
    {
        DLOG_F(INFO, "[OpenGL] Unbinding VAO %d", vaoIdx);
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::bindAttribute(Shader* shader, const hash& nameHash)
    {
        shader->use();
        const auto& vertexAttributeDef = getAttribute(nameHash);
        const auto shaderID = queryGLShaderID();
        const auto attributeID = queryAttributeLocation(shaderID, vertexAttributeDef.name.c_str());

        glBindVertexArray(this->vaoIdx);
        vertexAttributeDef.buffer->bind(BufferBindTarget::VERTEX);

        switch (vertexAttributeDef.dataType)
        {
        case DataType::INT:
            bindIntAttribute(attributeID, vertexAttributeDef, GL_INT);
            break;
        case DataType::UINT:
            bindIntAttribute(attributeID, vertexAttributeDef, GL_UNSIGNED_INT);
            break;
        case DataType::FLOAT:
            bindFloatAttribute(attributeID, vertexAttributeDef, GL_FLOAT);
            break;
        case DataType::DOUBLE:
            bindDoubleAttribute(attributeID, vertexAttributeDef);
            break;
        }

        glVertexAttribDivisor(attributeID, static_cast<GLuint>(vertexAttributeDef.updateDivisor));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        shader->disable();
    }

    void OpenGLVertexArray::enableAttribute(Shader* shader, const hash& nameHash)
    {
        shader->use();
        glBindVertexArray(this->vaoIdx);
        glEnableVertexAttribArray(queryAttributeLocationByHash(nameHash));
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::disableAttribute(Shader* shader, const hash& nameHash)
    {
        shader->use();
        glBindVertexArray(this->vaoIdx);
        glDisableVertexAttribArray(queryAttributeLocationByHash(nameHash));
        glBindVertexArray(0);
        shader->disable();
    }

    OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &vaoIdx); }

} // namespace blitz::ogl
