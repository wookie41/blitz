#include <core/BufferRange.h>
#include <core/Shader.h>
#include <core/UniformBlock.h>
#include <core/VertexArray.h>

namespace blitz
{
    Shader::Shader(Array<IUniformVariable*>* uniforms, Array<UniformBlock>* uniformBlocks, Array<ShaderOutput>* outputs)
    : uniformVariables(uniforms), uniformBlocks(uniformBlocks), shaderOutputs(outputs)
    {
    }

    Shader::~Shader()
    {
        delete uniformVariables;
        delete uniformBlocks;
        delete shaderOutputs;
    }

    void Shader::setUniformBlockBuffer(const hash& blockNameHash, BufferRange* bufferRange)
    {
        for (size_t blockIdx = 0; blockIdx < uniformBlocks->getSize(); ++blockIdx)
        {
            UniformBlock* uniformBlock = uniformBlocks->get(blockIdx);
            if (uniformBlock->blockName.getHash() == blockNameHash)
            {
                uniformBlock->associatedBuffer = bufferRange;
            }
        }
    }
} // namespace blitz