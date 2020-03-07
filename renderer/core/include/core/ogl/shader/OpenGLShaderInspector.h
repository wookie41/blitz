#pragma once

#include <core/Precompiled.h>
#include <core/ShaderOutput.h>

namespace blitz
{
    struct UniformBlock;
    class IUniformVariable;
} // namespace blitz

namespace blitz::ogl
{
    class OpenGLShaderInspector : NonCopyable
    {
      public:
        // hashes in the maps are hashes of the names of the attributes/uniforms
        Array<IUniformVariable*>* extractUniformVariables(const GLuint& shaderID, const Array<UniformBlock>* uniformBlocks) const;
        Array<UniformBlock>* extractUniformBlocks(const GLuint& shaderID) const;
        void createBindingPoints(GLuint shaderID, const Array<UniformBlock>* uniformBlocks) const;
        Array<ShaderOutput>* extractShaderOutputs(GLuint shaderID) const;
    };
} // namespace blitz::ogl