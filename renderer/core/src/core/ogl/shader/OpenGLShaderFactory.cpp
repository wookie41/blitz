#include <core/ogl/shader/OpenGLShaderFactory.h>

#include <core/ogl/shader/OpenGLShader.h>
#include <core/ogl/shader/OpenGLShaderCompiler.h>
#include <core/ogl/shader/OpenGLShaderInspector.h>

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
        const auto uniformBlocks = inspector->extractUniformBlocks(shaderID);
        const auto uniformVariables = inspector->extractUniformVariables(shaderID, uniformBlocks);
        const auto bindingPoints = inspector->createBindingPoints(shaderID, uniformBlocks);
        const auto outputs = inspector->extractShaderOutputs(shaderID);
        return new OpenGLShader(shaderSource.name, shaderID, uniformVariables, uniformBlocks, bindingPoints, outputs);
    }
} // namespace blitz