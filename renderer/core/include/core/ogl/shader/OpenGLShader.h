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
                     const std::unordered_map<hash, UniformBlock*>& unifomBlocks);

        GLuint shaderID;
        std::mutex mx;
        std::vector<GLuint> availableBindingPoints;
    };
} // namespace blitz
