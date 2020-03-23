#include <front/ShadersManager.h>
#include <core/Globals.h>
#include <core/Device.h>
#include <core/Shader.h>
#include <platform/fs/FileSystem.h>

namespace blitz::front
{
    Shader* ShadersManager::createShader(const hash& shaderNameHash, const ShaderSource& sources)
    {
        Shader* shader = shaders[shaderNameHash];
        if (shader != nullptr)
        {
            return shader;
        }

        shader = BLITZ_DEVICE->createShader(sources);
        shaders.set(shaderNameHash, shader);
        return shader;
    }

    Shader* ShadersManager::createShader(const hash& shaderNameHash, const ShadersPaths& paths)
    {
        char* vertexSource = fs::readFile(paths.vertexShaderFilePath);
        assert(vertexSource);

        char* geometrySource = nullptr;
        if (paths.geomtryShaderFilePath.getLength())
        {
            fs::readFile(paths.geomtryShaderFilePath);
            assert(geometrySource);
        }

        char* fragmentSource = fs::readFile(paths.fragmentShaderFilePath);
        assert(fragmentSource);

        Shader* shader = createShader(shaderNameHash, { vertexSource, geometrySource, fragmentSource });

        delete vertexSource;
        delete geometrySource;
        delete fragmentSource;

        return shader;
    }
} // namespace blitz::front
