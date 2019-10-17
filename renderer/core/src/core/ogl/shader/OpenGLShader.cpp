#include <core/BufferRange.h>
#include <core/UniformBlock.h>
#include <core/UniformVariable.h>
#include <core/VertexArray.h>
#include <core/ogl/buffer/OpenGLBuffer.h>
#include <core/ogl/shader/OpenGLShader.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>
#include <loguru.hpp>
#include <utility>

namespace blitz
{
    static std::unordered_map<hash, Buffer*> currentUniformBlockBindings;

    OpenGLShader::OpenGLShader(const std::string& name,
                               GLuint shaderID,
                               const std::unordered_map<hash, IUniformVariable*>& uniforms,
                               const std::unordered_map<hash, UniformBlock*>& unifomBlocks,
                               const std::unordered_map<hash, GLuint>& uniformBlockBindings,
                               const std::vector<ShaderOutput>& outputs)
    : Shader(name, uniforms, unifomBlocks, outputs), shaderID(shaderID), glBindPoints(uniformBlockBindings)
    {
    }

    void OpenGLShader::use()
    {
        DLOG_F(INFO, "[OpenGL] Using shader %d", shaderID);
        if (vertexArray == nullptr)
        {
            DLOG_F(ERROR, "[OpenGL] Vertex array is null on shader '%s'", shaderName.c_str());
        }
        else
        {
            vertexArray->bind();
        }

        glUseProgram(shaderID);
        bindDirtyVariables();
        bindUniformBlocks();
        bindSamplers();
    }

    void OpenGLShader::bindUniformBlock(const std::string& blockName, const BufferRange* bufferRange)
    {
        const auto blockNameHash = hashString(blockName);
        uniformBlocksBuffers[blockNameHash] = bufferRange;
    }

    void OpenGLShader::bindUniformBlocks() const
    {
        for (const auto& glBindPoint : glBindPoints)
        {
            const auto bufferIt = uniformBlocksBuffers.find(glBindPoint.first);
            if (bufferIt == uniformBlocksBuffers.end())
            {
                DLOG_F(ERROR, "[OpenGL] No buffer specified for binding point %d in shader '%s'", glBindPoint.second,
                       shaderName.c_str());
                continue;
            }

            auto glBuffer = dynamic_cast<OpenGLBuffer*>(bufferIt->second->buffer);
            if (glBuffer == nullptr)
            {
                DLOG_F(ERROR, "[OpenGL] Couldn't bind uniform block %d in shader '%s', the buffer is not a GL buffer",
                       glBindPoint.second, shaderName.c_str());
                continue;
            }

            const auto& currentBindingIt = currentUniformBlockBindings.find(glBindPoint.first);

            if (currentBindingIt != currentUniformBlockBindings.end() && currentBindingIt->second == glBuffer)
            {
                continue;
            }

            const auto uniformBlock = uniformBlocks.find(glBindPoint.first)->second;
            DLOG_F(INFO, "[OpenGL] Binding buffer %d to uniform block '%s' in shader '%s'", glBuffer->getId(),
                   uniformBlock->name, shaderName.c_str());

            glUniformBlockBinding(shaderID, uniformBlock->index, glBindPoint.second);

            const auto bufferSize = bufferIt->second->size;
            const auto bufferOffset = bufferIt->second->offset;

            if (bufferSize > 0 || bufferOffset > 0)
            {
                glBindBufferRange(GL_UNIFORM_BUFFER, uniformBlock->index, glBuffer->getId(), bufferOffset, bufferSize);
            }
            else
            {
                glBindBufferBase(GL_UNIFORM_BUFFER, uniformBlock->index, glBuffer->getId());
            }

            currentUniformBlockBindings[glBindPoint.first] = glBuffer;
        }
    }

    void OpenGLShader::bindSamplers()
    {
        auto textureCount = 0;
        auto textureCounter = GL_TEXTURE0;

        OpenGLUniformVariable* glVariable;
        for (const auto sampler : samplers)
        {
            glVariable = dynamic_cast<OpenGLUniformVariable*>(sampler);
            if (glVariable == nullptr)
                continue;
            glActiveTexture(textureCounter++);
            glUniform1i(glVariable->getVariableLocation(), textureCount++);
            sampler->bind();
        }
    }
} // namespace blitz
