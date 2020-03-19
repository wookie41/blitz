#include <blitzcommon/DataType.h>
#include <core/BasicRenderer.h>
#include <core/Framebuffer.h>
#include <core/RenderPass.h>
#include <core/RenderState.h>
#include <core/Shader.h>
#include <core/VertexArray.h>
#include <core/Window.h>
#include <core/Buffer.h>

namespace blitz
{

    void BasicRenderer::issue(RenderPass* renderPass) { renderPasses.push_back(renderPass); }

    void BasicRenderer::render()
    {
        Shader* lastShader = nullptr;
        Framebuffer* lastFramebuffer = nullptr;

        while (!renderPasses.empty())
        {
            RenderPass* renderPass = renderPasses.front();
            renderPasses.pop_front();

            const RenderState* renderState = renderPass->getRenderState();
            setViewPort(renderState->viewPort);

            setDepthTest(renderState->enableDepthTest);
            setStencilTest(renderState->enableStencilTest);
            setBlendTest(renderState->enableBlendTest);

            Shader* shader = renderState->shader;
            Framebuffer* framebuffer = renderState->framebuffer;

            if (framebuffer != lastFramebuffer)
            {
                framebuffer->bind();
                lastFramebuffer = framebuffer;
            }

            if (lastShader != shader)
            {
                if (lastShader != nullptr)
                    lastShader->disable();

                lastShader = shader;
                shader->use();
            }

            updateUniforms(shader, renderState->renderPassWideUniforms);

            RenderCommand* renderCommand = renderPass->getNextCommand();
            while (renderCommand != nullptr)
            {
                renderCommand->vertexArray->bind();
                // TODO this doesn't have to happen every time
                // ideally we would like to have vertex attributes description
                // that can be compared here and allow to determine wether the layout changed

                renderCommand->vertexArray->setupAttributes();
                if (renderCommand->buffers != nullptr)
                {
                    for (uint32 bindingIdx = 0; bindingIdx < renderCommand->buffers->getSize(); ++bindingIdx)
                    {
                        BufferBinding* binding = renderCommand->buffers->get(bindingIdx);
                        binding->bufferRange->buffer->bind(
                        { binding->bufferRange->offset, binding->bufferRange->size, 0, binding->bindTarget });
                    }
                }

                updateUniforms(shader, renderCommand->uniformsState);
                shader->setup();

                run(renderCommand);
                renderCommand->vertexArray->unbind();

                renderCommand = renderPass->getNextCommand();
            }
        }
    }

    void BasicRenderer::updateUniforms(Shader* shader, Array<UniformState>* uniformsState)
    {
        for (uint32 uniformIdx = 0; uniformIdx < uniformsState->getSize(); ++uniformIdx)
        {
            UniformState* uniformState = uniformsState->get(uniformIdx);
            switch (uniformState->dataType)
            {
            case DataType::BOOL:
                updateUniform<bool>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::INT:
                updateUniform<int32>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::UINT:
                updateUniform<uint32>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::FLOAT:
                updateUniform<float>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::DOUBLE:
                updateUniform<double>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::VECTOR2I:
                updateUniform<Vector2i>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::VECTOR3I:
                updateUniform<Vector3i>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::VECTOR2F:
                updateUniform<Vector2f>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::VECTOR3F:
                updateUniform<Vector3f>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::VECTOR4F:
                updateUniform<Vector4f>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::MATRIX3F:
                updateUniform<Matrix3f>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::MATRIX4F:
                updateUniform<Matrix4f>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
            case DataType::SAMPLER1D:
            case DataType::SAMPLER2D:
            case DataType::SAMPLER3D:
                updatePtrUniform<TextureSampler>(shader, uniformState->uniformNameHash, uniformState->value);
                break;
                // TODO Add more
            default:
                assert(false);
            }
        }
    }

    template <typename T>
    void BasicRenderer::updateUniform(Shader* shader, const hash& uniformNameHash, void* value)
    {
        UniformVariable<T>* uniformVariable = shader->getUniformVariable<T>(uniformNameHash);
        if (uniformVariable != nullptr)
        {
            *uniformVariable = *(T*)(value);
        }
    }

    template <typename T>
    void BasicRenderer::updatePtrUniform(Shader* shader, const hash& uniformNameHash, void* value)
    {
        UniformVariable<T*>* uniformVariable = shader->getUniformVariable<T*>(uniformNameHash);
        if (uniformVariable != nullptr)
        {
            *uniformVariable = (T*)(value);
        }
    }

} // namespace blitz