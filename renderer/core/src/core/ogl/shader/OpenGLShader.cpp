#include <core/ogl/shader/OpenGLShader.h>
#include <core/BufferRange.h>
#include <core/Framebuffer.h>
#include <core/UniformBlock.h>
#include <core/UniformVariable.h>
#include <core/VertexArray.h>
#include <core/ogl/buffer/OpenGLBuffer.h>
#include <core/ogl/framebuffer/OpenGLTextureAttachment.h>
#include <core/ogl/texture/OpenGLTexture.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>
#include <loguru.hpp>
#include <utility>

namespace blitz::ogl
{
    static std::unordered_map<hash, Buffer*> currentUniformBlockBindings;

    OpenGLShader::OpenGLShader(const std::string& name,
                               GLuint shaderID,
                               const std::unordered_map<hash, IUniformVariable*>& uniforms,
                               const std::unordered_map<hash, UniformBlock*>& uniformBlock,
                               const std::unordered_map<hash, GLuint>& uniformBlockBindings,
                               const std::unordered_map<hash, ShaderOutput*>& outputs)
    : Shader(name, uniforms, uniformBlock, outputs), shaderID(shaderID), glBindPoints(uniformBlockBindings)
    {
    }

    void OpenGLShader::use()
    {
        DLOG_F(INFO, "[OpenGL] Using shader %d", shaderID);
        glUseProgram(shaderID);
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
            if (glVariable == nullptr || !sampler->isDirty())
                continue;
            glActiveTexture(textureCounter++);
            glUniform1i(glVariable->getVariableLocation(), textureCount++);
            sampler->bind();
        }
    }

    void OpenGLShader::setOutputTarget(const hash& outputNameHash, Texture* targetTexture)
    {
        Shader::setOutputTarget(outputNameHash, targetTexture);
        newlyAddedOutputs.push_back(outputNameHash);
    }

    void OpenGLShader::setupOutputs(Framebuffer* targetFramebuffer)
    {
        if (targetFramebuffer == lastFrameBuffer && newlyAddedOutputs.empty())
            return;

        if (targetFramebuffer != lastFrameBuffer)
        {
            for (const auto& output : shaderOutputs)
                newlyAddedOutputs.push_back(output.first);
        }

        lastFrameBuffer = targetFramebuffer;

        for (const auto& outputNameHash : newlyAddedOutputs)
        {
            const auto output = shaderOutputs[outputNameHash];
            const auto glTexture = dynamic_cast<OpenGLTexture*>(output->texture);
            const auto glTextureAttachment = new OpenGLTextureAttachment(glTexture, GL_COLOR_ATTACHMENT0, false);

            targetFramebuffer->setColorAttachment(output->outputIdx, glTextureAttachment);
        }

        newlyAddedOutputs.clear();
    }

    void OpenGLShader::setup(Framebuffer* framebuffer)
    {
        if (framebuffer == nullptr)
        {
            DLOG_F(ERROR, "[OpenGL] Vertex array is null on shader '%s'", shaderName.c_str());
            return;
        }

        setupOutputs(framebuffer);
        bindDirtyVariables();
        bindUniformBlocks();
        bindSamplers();
    }

    void OpenGLShader::disable() { glUseProgram(0); }
} // namespace blitz::ogl
