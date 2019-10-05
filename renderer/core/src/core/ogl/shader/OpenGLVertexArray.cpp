#include <core/ogl/OpenGLContext.h>
#include <core/ogl/shader/OpenGLVertexArray.h>

#include <core/RendererErrorCode.h>
#include <loguru.hpp>


namespace blitz
{
    void bindBuffer(GLuint vaoIdx, Buffer* buffer, const BindTarget& target)
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

        if (shaderID)
        {
            exit(RendererErrorCode::OPENGL_NO_SHADER_BOUND);
        }

        return shaderID;
    }

    GLuint queryAttributeLocation(const GLint& shaderID, const char* name)
    {
        GLuint attributeIdx = static_cast<GLuint>(glGetAttribLocation(shaderID, name));

        if (attributeIdx == -1)
        {
            exit(RendererErrorCode::OPENGL_ATTRIBUTE_LOCATION_QUERY_FAILED);
        }

        return attributeIdx;
    }

    GLuint OpenGLVertexArray::queryAttributeLocationByHash(const hash& nameHash) const
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

    void OpenGLVertexArray::bindVertexBuffer(Buffer* buffer)
    {
        vertexBuffer = buffer;
        openGLContext->run([this](Context* context) { bindBuffer(vaoIdx, vertexBuffer, BindTarget::VERTEX); });
    }

    void OpenGLVertexArray::bindElementBuffer(Buffer* buffer)
    {
        elementBuffer = buffer;
        openGLContext->run([this](Context* context) { bindBuffer(vaoIdx, elementBuffer, BindTarget::ELEMENT); });
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

    void OpenGLVertexArray::bindAttribute(const hash& nameHash)
    {
        const auto& vertexAttributeDef = getAttribute(nameHash);
        const auto shaderID = queryGLShaderID();
        const auto attributeID = queryAttributeLocation(shaderID, vertexAttributeDef.name.c_str());

        glBindVertexArray(this->vaoIdx);
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

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::enable(const hash& nameHash)
    {
        glEnableVertexAttribArray(queryAttributeLocationByHash(nameHash));
    }

    void OpenGLVertexArray::disable(const hash& nameHash)
    {
        glDisableVertexAttribArray(queryAttributeLocationByHash(nameHash));
    }

    OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &vaoIdx); }

} // namespace blitz
