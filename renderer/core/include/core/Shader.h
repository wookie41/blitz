#pragma once

#include <core/Precompiled.h>
#include <core/RendererErrorCode.h>
#include <core/ShaderOutput.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class Buffer;
    class Framebuffer;
    class TextureSampler;
    class VertexArray;

    struct UniformBlock;
    struct BufferRange;

    class Shader : public NonCopyable
    {
      public:
        Shader(const blitz::string& name, Array<IUniformVariable*>* uniforms, Array<UniformBlock>* uniformBlocks, Array<ShaderOutput>* outputs);

        virtual void use() = 0;
        virtual void disable() = 0;

        void setUniformBlockBuffer(const hash& blockNameHash, BufferRange* bufferRange);

        virtual ~Shader();

      protected:
        blitz::string shaderName;
        Array<IUniformVariable*>* uniformVariables;
        Array<UniformBlock>* uniformBlocks;
        Array<ShaderOutput>* shaderOutputs;
    };
} // namespace blitz
