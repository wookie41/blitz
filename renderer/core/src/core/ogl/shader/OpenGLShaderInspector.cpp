#include <core/ogl/shader/OpenGLShaderInspector.h>

#include <core/Max.h>
#include <core/UniformBlock.h>
#include <core/ogl/OpenGLDataType.h>

#include <core/ogl/uniforms/OpenGLBoolUniformVariable.h>
#include <core/ogl/uniforms/OpenGLDoubleUniformVariable.h>
#include <core/ogl/uniforms/OpenGLFloatUniformVariable.h>
#include <core/ogl/uniforms/OpenGLIntegerUniformVariable.h>
#include <core/ogl/uniforms/OpenGLMat3UniformVariable.h>
#include <core/ogl/uniforms/OpenGLMat4UniformVariable.h>
#include <core/ogl/uniforms/OpenGLSamplerUniformVariable.h>
#include <core/ogl/uniforms/OpenGLVec3UniformVariable.h>
#include <core/ogl/uniforms/OpenGLVec4UniformVariable.h>

namespace blitz::ogl
{
    Array<IUniformVariable*>*
    OpenGLShaderInspector::extractUniformVariables(const GLuint& shaderID, const Array<UniformBlock>* uniformBlocks) const
    {
        GLint numberOfUniforms;
        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

        Array<hash> blockUniformsHashes(numberOfUniforms);
        Array<IUniformVariable*>* uniforms = new Array<IUniformVariable*>(numberOfUniforms);

        for (uint32 idx = 0; idx < uniformBlocks->getSize(); ++idx)
        {
            UniformBlock* block = uniformBlocks->get(idx);
            for (uint16_t fieldIdx = 0; fieldIdx < block->blockFields->getSize(); ++fieldIdx)
            {
                blockUniformsHashes.add(block->blockFields->get(fieldIdx)->fieldName.getHash());
            }
        }

        GLint size;
        GLenum type;
        GLsizei nameLength;

        GLint samplersCount = 0;
        char uniformNameBuff[MAX_UNIFORM_VARIABLE_NAME_LENGTH];

        for (GLint uniformIdx = 0; uniformIdx < numberOfUniforms; ++uniformIdx)
        {
            glGetActiveUniform(shaderID, uniformIdx, MAX_UNIFORM_VARIABLE_NAME_LENGTH, &nameLength, &size, &type, uniformNameBuff);
            uniformNameBuff[nameLength] = '\0';

            const auto uniformNameHash = hashString(uniformNameBuff, nameLength);
            if (blockUniformsHashes.contains(uniformNameHash))
            {
                continue;
            }

            GLint variableLocation = glGetUniformLocation(shaderID, uniformNameBuff);
            char* variableName = new char[nameLength];
            strncpy(variableName, uniformNameBuff, nameLength);

            blitz::string name(variableName, nameLength);

            switch (type)
            {
            case GL_BOOL:
                uniforms->add(new OpenGLBoolUniformVariable(variableLocation, 0, name));
                break;
            case GL_INT:
                uniforms->add(new OpenGLIntegerUniformVariable(variableLocation, 0, name));
                break;
            case GL_FLOAT:
                uniforms->add(new OpenGLFloatUniformVariable(variableLocation, 0, name));
                break;
            case GL_DOUBLE:
                uniforms->add(new OpenGLDoubleUniformVariable(variableLocation, 0, name));
                break;
            case GL_FLOAT_VEC3:
                uniforms->add(new OpenGLVec3UniformVariable(variableLocation, {}, name));
                break;
            case GL_FLOAT_VEC4:
                uniforms->add(new OpenGLVec4UniformVariable(variableLocation, {}, name));
                break;
            case GL_FLOAT_MAT3:
                uniforms->add(new OpenGLMat3UniformVariable(variableLocation, {}, name));
                break;
            case GL_FLOAT_MAT4:
                uniforms->add(new OpenGLMat4UniformVariable(variableLocation, {}, name));
                break;
            case GL_SAMPLER_1D:
                uniforms->add(new OpenGLSamplerUniformVariable(variableLocation, nullptr, name, GL_SAMPLER_1D));
                glUniform1i(variableLocation, samplersCount++);
                break;
            case GL_SAMPLER_2D:
                uniforms->add(new OpenGLSamplerUniformVariable(variableLocation, nullptr, name, GL_SAMPLER_2D));
                glUniform1i(variableLocation, samplersCount++);
                break;
            case GL_SAMPLER_3D:
                uniforms->add(new OpenGLSamplerUniformVariable(variableLocation, nullptr, name, GL_SAMPLER_3D));
                glUniform1i(variableLocation, samplersCount++);
                break;
            default:
                DLOG_F(ERROR, "[OpenGL] Unsupported uniform variable type for '%s'", name);
            }
        }

        DLOG_F(INFO, "[OpenGL] Program %ld has %d uniforms ", shaderID, uniforms->getSize());
        return uniforms;
    }

    Array<UniformBlock>* OpenGLShaderInspector::extractUniformBlocks(const GLuint& shaderID) const
    {
        GLint uniformBlocksNum;
        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlocksNum);

        assert(uniformBlocksNum > -1);

        Array<UniformBlock>* uniformBlocks = new Array<UniformBlock>(uniformBlocksNum);

        GLuint uniformBlockIdx = 0;

        GLsizei nameLength;
        GLint type, offset;

        GLchar uniformBlockName[MAX_UNIFORM_BLOCK_NAME_LENGTH];
        GLchar uniformBlockFieldName[MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH];

        while (uniformBlockIdx < uniformBlocksNum)
        {
            nameLength = 0;

            glGetActiveUniformBlockName(shaderID, uniformBlockIdx, MAX_UNIFORM_BLOCK_NAME_LENGTH, &nameLength, uniformBlockName);
            assert(nameLength > 0);

            const GLuint uniformBlockIndex = glGetUniformBlockIndex(shaderID, uniformBlockName);

            if (uniformBlockIndex != GL_INVALID_INDEX)
            {
                char* blockName = new char[nameLength];
                strncpy(blockName, uniformBlockName, nameLength);

                int numFieldsInBlock;
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numFieldsInBlock);
                Array<UniformBlockField>* blockFields = new Array<UniformBlockField>(numFieldsInBlock);

                int* fieldsIndicies = new int[numFieldsInBlock];
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, fieldsIndicies);

                for (int fieldIdx = 0; fieldIdx < numFieldsInBlock; ++fieldIdx)
                {
                    const uint32& glFieldIndex = (uint32)fieldsIndicies[fieldIdx];

                    glGetActiveUniformName(shaderID, glFieldIndex, MAX_UNIFORM_BLOCK_FIELD_NAME_LENGTH, &nameLength,
                                           uniformBlockFieldName);

                    glGetActiveUniformsiv(shaderID, 1, &glFieldIndex, GL_UNIFORM_TYPE, &type);
                    glGetActiveUniformsiv(shaderID, 1, &glFieldIndex, GL_UNIFORM_OFFSET, &offset);

                    char* fieldName = new char[nameLength];
                    strncpy(fieldName, uniformBlockFieldName, nameLength);

                    blockFields->add({ blitz::string(fieldName, nameLength), mapToBlitzDataType(type), offset });
                }

                GLint binding = 0;
                glGetActiveUniformBlockiv(shaderID, uniformBlockIndex, GL_UNIFORM_BLOCK_BINDING, &binding);

                uniformBlocks->add({ uniformBlockIndex, (int8)(binding == 0 ? -1 : binding),
                                     blitz::string(blockName, nameLength), blockFields });
            }

            uniformBlockIdx++;
        }

        return uniformBlocks;
    }

    void OpenGLShaderInspector::createBindingPoints(const GLuint shaderID, const Array<UniformBlock>* uniformBlocks) const
    {
        int8 bindingsTaken[16];
        int8 bindingsTakenCount = 0;

        for (size_t blockIdx = 0; blockIdx < uniformBlocks->getSize(); ++blockIdx)
        {
            int8 uniformBindingPoint = uniformBlocks->get(blockIdx)->bindingPoint;
            if (uniformBindingPoint != -1)
            {
                bindingsTaken[bindingsTakenCount++] = uniformBindingPoint;
            }
        }

        int8 nextFreeBinding = 0;
        for (size_t blockIdx = 0; blockIdx < uniformBlocks->getSize(); ++blockIdx)
        {
            if (uniformBlocks->get(blockIdx)->bindingPoint != -1)
            {
                continue;
            }

            while (true)
            {
                bool bindingFound = true;
                for (int8 bindingIdx = 0; bindingIdx < bindingsTakenCount; ++bindingIdx)
                {
                    if (bindingsTaken[bindingIdx] == nextFreeBinding)
                    {
                        ++nextFreeBinding;
                        bindingFound = false;
                        break;
                    }
                }

                if (bindingFound)
                    break;
            }

            bindingsTaken[bindingsTakenCount] = nextFreeBinding++;
            uniformBlocks->get(blockIdx)->bindingPoint = bindingsTaken[bindingsTakenCount++];
            glUniformBlockBinding(shaderID, uniformBlocks->get(blockIdx)->index, uniformBlocks->get(blockIdx)->bindingPoint);
        }
    }

    Array<ShaderOutput>* OpenGLShaderInspector::extractShaderOutputs(GLuint shaderID) const
    {
        static const GLenum propertiesToQuery[] = { GL_TYPE, GL_LOCATION };
        char outputName[MAX_FRAGMENT_OUTPUT_NAME_LENGTH];

        GLint outputsCount;
        glGetProgramInterfaceiv(shaderID, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &outputsCount);

        Array<ShaderOutput>* shaderOutputs = new Array<ShaderOutput>(outputsCount);

        GLint properties[2];
        int outputNameLength;

        for (GLint outputIdx = 0; outputIdx < outputsCount; ++outputIdx)
        {
            glGetProgramResourceName(shaderID, GL_PROGRAM_OUTPUT, outputIdx, MAX_FRAGMENT_OUTPUT_NAME_LENGTH,
                                     &outputNameLength, outputName);

            char* name = new char[outputNameLength];
            strncpy(name, outputName, outputNameLength);

            glGetProgramResourceiv(shaderID, GL_PROGRAM_OUTPUT, outputIdx, 2, propertiesToQuery, 2, nullptr, properties);

            DLOG_F(ERROR, "[OpenGL] Shader output %d is named '%s' and is of type %s", outputIdx, outputName,
                   typeToName(properties[0]));

            if (outputNameLength > MAX_FRAGMENT_OUTPUT_NAME_LENGTH)
            {
                DLOG_F(ERROR, "[OpenGL] Output number %d has too long of a name", outputIdx);
            }

            shaderOutputs->add({ static_cast<uint16>(outputIdx),
                                 properties[0] == GL_FLOAT_VEC3 ? TextureFormat::RGB : TextureFormat::RGBA,
                                 blitz::string(name, outputNameLength) });
        }
        DLOG_F(INFO, "[OpenGL] Shader %d has %d outputs", shaderID, outputsCount);

        return shaderOutputs;
    }
} // namespace blitz::ogl