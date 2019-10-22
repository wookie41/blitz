#include <core/ogl/shader/OpenGLShaderInspector.h>
#include <loguru.hpp>

#include <core/Max.h>
#include <core/UniformBlock.h>
#include <core/ogl/OpenGLDataType.h>
#include <cstring>
#include <unordered_set>

#include <core/ogl/uniforms/OpenGLDoubleUniformVariable.h>
#include <core/ogl/uniforms/OpenGLFloatUniformVariable.h>
#include <core/ogl/uniforms/OpenGLIntegerUniformVariable.h>
#include <core/ogl/uniforms/OpenGLMat3UniformVariable.h>
#include <core/ogl/uniforms/OpenGLMat4UniformVariable.h>
#include <core/ogl/uniforms/OpenGLSampler1DUniformVariable.h>
#include <core/ogl/uniforms/OpenGLSampler2DUniformVariable.h>
#include <core/ogl/uniforms/OpenGLSampler3DUniformVariable.h>
#include <core/ogl/uniforms/OpenGLVec3UniformVariable.h>
#include <core/ogl/uniforms/OpenGLVec4UniformVariable.h>


namespace blitz::ogl
{
    std::unordered_map<hash, IUniformVariable*>
    OpenGLShaderInspector::extractUniformVariables(GLuint shaderID, const std::unordered_map<hash, UniformBlock*>& uniformBlocks)
    {
        std::unordered_set<hash> blockUniforms;
        std::unordered_map<hash, IUniformVariable*> uniforms;

        for (const auto& it : uniformBlocks)
        {
            const auto block = it.second;
            for (uint16_t i = 0; i < block->numberOfFields; ++i)
            {
                blockUniforms.insert(hashString(block->fields[i].name));
            }
        }

        GLint numberOfUniforms;
        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

        GLint size;
        GLenum type;
        GLsizei nameLength;
        char name[MAX_UNIFORM_VARIABLE_NAME_LENGTH];

        for (GLuint uniformIdx = 0; uniformIdx < numberOfUniforms; ++uniformIdx)
        {
            glGetActiveUniform(shaderID, uniformIdx, MAX_UNIFORM_VARIABLE_NAME_LENGTH, &nameLength, &size, &type, name);

            const auto nameHash = hashString(name);
            if (blockUniforms.find(nameHash) != blockUniforms.end())
            {
                continue;
            }

            auto variableLocation = glGetUniformLocation(shaderID, name);
            switch (type)
            {
            case GL_INT:
                uniforms[nameHash] = new OpenGLIntegerUniformVariable(variableLocation, 0, name);
                break;
            case GL_FLOAT:
                uniforms[nameHash] = new OpenGLFloatUniformVariable(variableLocation, 0, name);
                break;
            case GL_DOUBLE:
                uniforms[nameHash] = new OpenGLDoubleUniformVariable(variableLocation, 0, name);
                break;
            case GL_FLOAT_VEC3:
                uniforms[nameHash] = new OpenGLVec3UniformVariable(variableLocation, {}, name);
                break;
            case GL_FLOAT_VEC4:
                uniforms[nameHash] = new OpenGLVec4UniformVariable(variableLocation, {}, name);
                break;
            case GL_FLOAT_MAT3:
                uniforms[nameHash] = new OpenGLMat3UniformVariable(variableLocation, {}, name);
                break;
            case GL_FLOAT_MAT4:
                uniforms[nameHash] = new OpenGLMat4UniformVariable(variableLocation, {}, name);
                break;
            case GL_SAMPLER_1D:
                uniforms[nameHash] = new OpenGLSampler1DUniformVariable(variableLocation, nullptr, name);
                break;
            case GL_SAMPLER_2D:
                uniforms[nameHash] = new OpenGLSampler2DUniformVariable(variableLocation, nullptr, name);
                break;
            case GL_SAMPLER_3D:
                uniforms[nameHash] = new OpenGLSampler3DUniformVariable(variableLocation, nullptr, name);
                break;

            default:
                DLOG_F(ERROR, "[OpenGL] Unsupported uniform variable type for '%s'", name);
            }
        }

        DLOG_F(INFO, "[OpenGL] Program %d has %ld uniforms ", shaderID, uniforms.size());
        return uniforms;
    }

    std::unordered_map<hash, UniformBlock*> OpenGLShaderInspector::extractUniformBlocks(GLuint shaderID)
    {
        std::unordered_map<hash, UniformBlock*> uniformBlocks;
        GLuint uniformBlockIdx = 0;

        GLsizei nameLength;
        GLint type, offset;
        GLchar uniformBlockName[MAX_UNIFORM_BLOCK_NAME_LENGTH];
        GLchar uniformBlockFieldName[MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH];

        while (uniformBlockIdx < GL_ACTIVE_UNIFORM_BLOCKS)
        {
            nameLength = 0;

            memset(uniformBlockName, 0, MAX_UNIFORM_BLOCK_NAME_LENGTH);
            glGetActiveUniformBlockName(shaderID, uniformBlockIdx, MAX_UNIFORM_BLOCK_NAME_LENGTH, &nameLength, uniformBlockName);
            if (nameLength == 0)
            {
                return uniformBlocks;
            }

            const auto uniformBlockIndex = glGetUniformBlockIndex(shaderID, uniformBlockName);

            if (uniformBlockIndex != GL_INVALID_INDEX)
            {
                const auto nameHash = hashString(uniformBlockName);
                uniformBlocks[nameHash] = new UniformBlock();

                const auto& uniformBlock = uniformBlocks[nameHash];
                uniformBlock->index = uniformBlockIndex;
                strncpy(uniformBlock->name, uniformBlockName, nameLength);

                int activeUniformsInBlock;
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniformsInBlock);
                uniformBlock->numberOfFields = activeUniformsInBlock;

                int* uniformsIndices = new int[activeUniformsInBlock];
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uniformsIndices);

                GLint binding = 999;
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_BINDING, &binding);
                for (uint i = 0; i < activeUniformsInBlock; ++i)
                {
                    const uint& index = (uint)uniformsIndices[i];

                    glGetActiveUniformName(shaderID, index, MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH, &nameLength, uniformBlockFieldName);

                    glGetActiveUniformsiv(shaderID, 1, &index, GL_UNIFORM_TYPE, &type);
                    glGetActiveUniformsiv(shaderID, 1, &index, GL_UNIFORM_OFFSET, &offset);

                    auto& field = uniformBlock->fields[i];
                    strncpy(field.name, uniformBlockFieldName, nameLength);
                    field.offset = offset;
                    field.dataType = mapToBlitzDataType(type);
                }
            }

            ++uniformBlockIdx;
        }

        return uniformBlocks;
    }

    std::unordered_map<hash, GLuint>
    OpenGLShaderInspector::createBindingPoints(const GLuint shaderID, const std::unordered_map<hash, UniformBlock*>& uniformBlocks)
    {
        GLint freeBinding = 0;
        std::unordered_map<hash, GLuint> bindings;
        for (const auto& it : uniformBlocks)
        {
            const auto block = it.second;
            GLint bindingPoint = -1;
            const auto uniformBlockIndex = glGetUniformBlockIndex(shaderID, block->name);

            if (uniformBlockIndex == GL_INVALID_INDEX)
            {
                DLOG_F(ERROR, "[OpenGL] Shader %d doesn't declare a uniform block named %s", shaderID, block->name);
                continue;
            }

            glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_BINDING, &bindingPoint);
            if (bindingPoint == -1)
            {
                DLOG_F(ERROR, "[OpenGL] Failed to query for binding of uniform block %s in shader %d", block->name, shaderID);
                continue;
            }

            bindingPoint = bindingPoint == 0 ? freeBinding++ : bindingPoint;
            glUniformBlockBinding(shaderID, uniformBlockIndex, static_cast<GLuint>(bindingPoint));

            bindings[it.first] = static_cast<GLuint>(bindingPoint);
        }

        return bindings;
    }

    std::unordered_map<hash, ShaderOutput*> OpenGLShaderInspector::extractShaderOutputs(GLuint shaderID)
    {
        static const GLenum propertiesToQuery[] = { GL_TYPE, GL_LOCATION };
        static char outputName[MAX_FRAGMENT_OUTPUT_NAME_LENGTH];

        std::unordered_map<hash, ShaderOutput*> outputs = {};

        GLint outputsCount;
        glGetProgramInterfaceiv(shaderID, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &outputsCount);


        GLint properties[2];
        int outputNameLength;

        for (GLuint outputIdx = 0; outputIdx < outputsCount; ++outputIdx)
        {
            memset(outputName, 0, MAX_UNIFORM_BLOCK_NAME_LENGTH);
            glGetProgramResourceName(shaderID, GL_PROGRAM_OUTPUT, outputIdx, MAX_FRAGMENT_OUTPUT_NAME_LENGTH,
                                     &outputNameLength, outputName);

            const auto hash = hashString(outputName);
            outputs[hash] = new ShaderOutput();
            ShaderOutput* output = outputs[hash];

            strncpy(output->name, outputName, static_cast<size_t>(outputNameLength));
            output->texture = nullptr;

            glGetProgramResourceiv(shaderID, GL_PROGRAM_OUTPUT, outputIdx, 2, propertiesToQuery, 2, nullptr, properties);
            output->outputIdx = static_cast<uint16>(properties[1]);

            switch (properties[0])
            {
            case GL_FLOAT_VEC3:
                output->textureFormat = TextureFormat::RGB;
                break;
            case GL_FLOAT_VEC4:
                output->textureFormat = TextureFormat::RGBA;
                break;
            default:
                DLOG_F(ERROR, "[OpenGL] Unknown shader output type %s", typeToName(properties[0]));
                continue;
            }

            DLOG_F(ERROR, "[OpenGL] Shader output %d is named '%s' and is of type %s", outputIdx, output->name, typeToName(properties[0]));
            if (outputNameLength > MAX_FRAGMENT_OUTPUT_NAME_LENGTH)
            {
                DLOG_F(ERROR, "[OpenGL] Output number %d has too long of a name", outputIdx);
            }
        }
        DLOG_F(INFO, "[OpenGL] Shader %d has %d outputs", shaderID, outputsCount);

        return outputs;
    }
} // namespace blitz::ogl