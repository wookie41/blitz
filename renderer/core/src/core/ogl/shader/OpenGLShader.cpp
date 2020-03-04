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
    static std::unordered_map<hash, Buffer*> currentUniformBlockBindings;

    OpenGLShader::OpenGLShader(const char* const name,
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
        glUseProgram(shaderID);

        // updating uniform variables if their value has changed and binding textures
        for (size_t uniformVariableIdx = 0; uniformVariableIndex < uniformVariables.size(), ++uniformVariableIndex)
        {
            GLenum textureCounter = GL_TEXTURE0;

            IUniformVariable* uniformVariable = *uniformVariables[uniformVariableIdx];

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

        // binding uniform blocks buffers to appropriate bindig points
        for (size_t blockIdx = 0; blockIdx < uniformBlocks->size(); ++blockIdx)
        {
            UniformBlock* uniformBlock = uniformBlocks[blockIdx];
            Buffer* blockBuffer = uniformBlock->associatedBuffer;
            if (blockBuffer == nullptr)
            {
                DLOG_F(INFO, "Uniform block %s has no associated buffer, skipping it", uniformBlock->blockName);
                continue;
            }

            blockBuffer->bind({ 0, blockBuffer->getSizeInBytes(), uniformBlock->index, BufferBindTarget::UNIFORM_BLOCK })
        }
    }

    void OpenGLShader::disable() { glUseProgram(0); }
} // namespace blitz::ogl
