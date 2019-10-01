#include <GL/glew.h>
#include <core/Shader.h>
#include <mutex>

namespace blitz
{

    class OpenGLShaderFactory;

    class OpenGLShader : public Shader
    {
        friend OpenGLShaderFactory;

      public:
        void use() override;

        void bindUniformBlock(const std::string& blockName, Buffer* buffer) override;

      private:
        OpenGLShader(const std::string& name,
                     GLuint shaderID,
                     const std::unordered_map<hash, IUniformVariable*>& uniforms,
                     const std::unordered_map<hash, UniformBlock*>& unifomBlocks,
                     const std::unordered_map<hash, GLuint>& uniformBlockBindings);

        GLuint shaderID;
        std::unordered_map<hash, GLuint> uniformBlockBindings;
        std::unordered_map<hash, Buffer*> uniformBlocksBuffers;

    };
} // namespace blitz
