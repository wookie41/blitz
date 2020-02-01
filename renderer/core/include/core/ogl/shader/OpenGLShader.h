#pragma once

#include <core/Precompiled.h>
#include <core/Shader.h>

namespace blitz::ogl
{
    class OpenGLShaderFactory;

    class OpenGLShader : public Shader
    {
        friend OpenGLShaderFactory;

      public:

        void setup(Framebuffer *framebuffer) override;

        void use() override;

        void disable() override;

        void bindUniformBlock(const hash& blockNameHash, const BufferRange* bufferRange) override;

        void setOutputTarget(const hash &outputNameHash, Texture *targetTexture) override;

    private:
        OpenGLShader(const char* const nameHash,
                     GLuint shaderID,
                     const std::unordered_map<hash, IUniformVariable*>& uniforms,
                     const std::unordered_map<hash, UniformBlock*>& uniformBlock,
                     const std::unordered_map<hash, GLuint>& uniformBlockBindings,
                     const std::unordered_map<hash, ShaderOutput*>& outputs);

        void bindUniformBlocks() const;
        void bindSamplers();
        void setupOutputs(Framebuffer *targetFramebuffer);

        GLuint shaderID;
        std::vector<hash> newlyAddedOutputs;
        std::unordered_map<hash, GLuint> glBindPoints;
        std::unordered_map<hash, const BufferRange*> uniformBlocksBuffers;
        Framebuffer* lastFrameBuffer = nullptr;
    };
} // namespace blitz::ogl
