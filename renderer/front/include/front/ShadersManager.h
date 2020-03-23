#pragma once

#include <front/Precompiled.h>
#include <core/ShaderSource.h>

namespace blitz
{
    class Shader;
    // This class is responsible of managing the sources of shaders
    // and actually making the shaders accessible to the rest of the system
    // It should eventually handle things like hod-reload of shaders on debug build
    // for ease of development
    namespace front
    {
        struct ShadersPaths
        {
            const blitz::string& vertexShaderFilePath;
            const blitz::string& geomtryShaderFilePath;
            const blitz::string& fragmentShaderFilePath;
        };

        class ShadersManager : public NonCopyable
        {
          public:
            ShadersManager() = default;

            Shader* createShader(const hash& shaderNameHash, const ShaderSource& sources);
            Shader* createShader(const hash& shaderNameHash, const ShadersPaths& paths);

          private:
            HashTable<Shader> shaders;
        };

    } // namespace front
} // namespace blitz