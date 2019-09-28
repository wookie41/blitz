#include <GL/glew.h>
#include <core/Shader.h>

namespace blitz
{

    class OpenGLShaderFactory;

    class OpenGLShader : public Shader
    {
        friend OpenGLShaderFactory;

      public:
        void use() override;

      private:
        OpenGLShader(GLuint shaderID, std::unordered_map<hash, IUniformVariable*> uniforms);

        GLuint shaderID;
    };
} // namespace blitz
