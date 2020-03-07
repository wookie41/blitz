#include <core/ogl/shader/OpenGLShader.h>
#include <core/ogl/shader/OpenGLShaderCompiler.h>
#include <core/ogl/shader/OpenGLShaderFactory.h>
#include <core/ogl/shader/OpenGLShaderInspector.h>

namespace blitz::ogl
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
        auto shaderID = compiler->compile(shaderSource);
        auto uniformBlocks = inspector->extractUniformBlocks(shaderID);
        auto uniformVariables = inspector->extractUniformVariables(shaderID, uniformBlocks);
        auto outputs = inspector->extractShaderOutputs(shaderID);
        inspector->createBindingPoints(shaderID, uniformBlocks);
        return new OpenGLShader(blitz::string(shaderSource.name), shaderID, uniformVariables, uniformBlocks, outputs);
    }
} // namespace blitz::ogl