#include <core/BufferRange.h>
#include <core/Framebuffer.h>
#include <core/UniformBlock.h>
#include <core/UniformVariable.h>
#include <core/VertexArray.h>
#include <core/ogl/buffer/OpenGLBuffer.h>
#include <core/ogl/framebuffer/OpenGLTextureAttachment.h>
#include <core/ogl/shader/OpenGLShader.h>
#include <core/ogl/texture/OpenGLTexture.h>
#include <core/ogl/uniforms/OpenGLSamplerUniformVariable.h>
#include <core/ogl/uniforms/OpenGLUniformVariable.h>

namespace blitz::ogl
{
    OpenGLShader::OpenGLShader(const GLuint& id, Array<IUniformVariable*>* uniforms, Array<UniformBlock>* uniformBlocks, Array<ShaderOutput>* outputs)
    : Shader(uniforms, uniformBlocks, outputs), shaderID(id)
    {
    }

    void OpenGLShader::use()
    {
        glUseProgram(shaderID);

        // binding uniform blocks buffers to appropriate bindig points
        for (size_t blockIdx = 0; blockIdx < uniformBlocks->getSize(); ++blockIdx)
        {
            UniformBlock* uniformBlock = uniformBlocks->get(blockIdx);
            BufferRange* blockBufferRange = uniformBlock->associatedBuffer;
            if (blockBufferRange == nullptr)
            {
                DLOG_F(INFO, "Uniform block %s has no associated buffer, skipping it", uniformBlock->blockName);
                continue;
            }

            blockBufferRange->buffer->bind(
            { blockBufferRange->offset, blockBufferRange->size, uniformBlock->index, BufferBindTarget::UNIFORM_BLOCK });
        }
    }

    void OpenGLShader::setup()
    {
        // updating uniform variables if their value has changed and binding textures
        for (size_t uniformVariableIdx = 0; uniformVariableIdx < uniformVariables->getSize(); ++uniformVariableIdx)
        {
            GLenum textureCounter = GL_TEXTURE0;

            IUniformVariable* uniformVariable = *(uniformVariables->get(uniformVariableIdx));

            if (uniformVariable->getType() == DataType::SAMPLER1D ||
                uniformVariable->getType() == DataType::SAMPLER2D || uniformVariable->getType() == DataType::SAMPLER3D)
            {
                glActiveTexture(textureCounter++);
                uniformVariable->bind();
                continue;
            }

            if (uniformVariable->isDirty())
            {
                uniformVariable->bind();
            }
        }
    }

    void OpenGLShader::disable() { glUseProgram(0); }
} // namespace blitz::ogl
