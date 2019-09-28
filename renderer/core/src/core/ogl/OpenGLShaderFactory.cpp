#include <core/ogl/OpenGLShaderFactory.h>

#include <core/ogl/OpenGLShader.h>
#include <core/ogl/OpenGLShaderCompiler.h>
#include <core/ogl/OpenGLShaderInspector.h>

namespace blitz
{
    OpenGLShaderFactory::OpenGLShaderFactory()
    {
        compiler = new OpenGLShaderCompiler();
        inspector = new OpenGLShaderInspector();
    }

    OpenGLShaderFactory::~OpenGLShaderFactory()
    {
        delete compiler;
        delete inspector;
    }

    Shader* OpenGLShaderFactory::createShader(const ShaderSource& shaderSource)
    {
        const auto shaderID = compiler->compile(shaderSource);
        const auto uniformVariables = inspector->extractUniformVariables(shaderID);
        return new OpenGLShader(shaderID, uniformVariables);
    }
} // namespace blitz