#include <core/ogl/OpenGLShaderInspector.h>
#include <loguru.hpp>

#include <core/Max.h>
#include <core/UniformBlock.h>
#include <core/ogl/DataType.h>
#include <core/ogl/OpenGLIntegerUniformVariable.h>
#include <cstring>

namespace blitz
{


    // TODO THIS SHOULD ACCEPT A COLLECTION OF UNIFORMS THAT BELONG TO A UNIFORM BLOCK SO THEY CEN SKIPPED
    std::unordered_map<hash, IUniformVariable*> OpenGLShaderInspector::extractUniformVariables(GLuint shaderID)
    {
        std::unordered_map<hash, IUniformVariable*> uniforms;

        GLint numberOfUniforms;

        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

        DLOG_F(INFO, "[OpenGL] Program %d has %d uniforms ", shaderID, numberOfUniforms);

        GLint size;
        GLenum type;
        GLsizei nameLength;
        char name[MAX_UNIFORM_VARIABLE_NAME_LENGTH];

        for (GLuint uniformIdx = 0; uniformIdx < numberOfUniforms; ++uniformIdx)
        {
            glGetActiveUniform(shaderID, uniformIdx, MAX_UNIFORM_VARIABLE_NAME_LENGTH, &nameLength, &size, &type, name);
            auto variableLocation = glGetUniformLocation(shaderID, name);
            switch (type)
            {
            case GL_INT:
                uniforms[hashString(name)] = new OpenGLIntegerUniformVariable(variableLocation, 0, name);
                break;
            default:
                DLOG_F(ERROR, "[OpenGL] Unsupported uniform variable '%s' type %d", name, type);
            }
        }

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

        while (uniformBlockIdx++ < GL_ACTIVE_UNIFORM_BLOCKS)
        {

            nameLength = 0;

            glGetActiveUniformBlockName(shaderID, uniformBlockIdx, MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH, &nameLength, uniformBlockName);
            if (nameLength == 0)
            {

                return uniformBlocks;
            }

            const auto uniformBlockIndex = glGetUniformBlockIndex(shaderID, uniformBlockName);


            if (uniformBlockIndex != GL_INVALID_INDEX)
            {
                const auto nameHash = hashString(uniformBlockName);
                uniformBlocks[nameHash] = {};

                const auto& uniformBlock = uniformBlocks[nameHash];
                strncpy(uniformBlock->name, uniformBlockName, nameLength);

                int activeUniformsInBlock;
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniformsInBlock);

                int* uniformsIndices = new int[activeUniformsInBlock];
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, uniformsIndices);

                for (uint i = 0; i < activeUniformsInBlock; i++)
                {
                    const uint& index = (uint)uniformsIndices[i];

                    glGetActiveUniformName(shaderID, index, MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH, &nameLength, uniformBlockFieldName);

                    glGetActiveUniformsiv(shaderID, 1, &index, GL_UNIFORM_TYPE, &type);
                    glGetActiveUniformsiv(shaderID, 1, &index, GL_UNIFORM_OFFSET, &offset);

                    auto& field = uniformBlock->fields[activeUniformsInBlock];
                    strncpy(field.name, uniformBlockFieldName, nameLength);
                    field.offset = offset;
                    field.dataType = mapToBlitzDataType(type);
                }
            }
        }
    }

} // namespace blitz