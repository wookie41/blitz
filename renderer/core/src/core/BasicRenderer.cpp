#include <GL/glew.h>
#include <core/BasicRenderer.h>
#include <core/DataType.h>
#include <core/Framebuffer.h>
#include <core/RenderCommand.h>
#include <core/RenderPass.h>
#include <core/RenderState.h>
#include <core/Shader.h>
#include <core/VertexArray.h>
#include <core/Window.h>

namespace blitz
{

    void BasicRenderer::issue(RenderPass* renderPass) { renderPasses.push_back(renderPass); }

    void BasicRenderer::render(Window* window)
    {
        window->prepare();
        Shader* lastShader = nullptr;
        Framebuffer* lastFramebuffer = nullptr;

        while (!renderPasses.empty())
        {
            RenderPass* renderPass = renderPasses.front();
            renderPasses.pop_front();

            const RenderState& renderState = renderPass->getRenderState();
            setViewPort(&renderState.viewPort);

            Shader* shader = renderState.shader;
            Framebuffer* framebuffer = renderState.framebuffer == nullptr ? window->getFramebuffer() : renderState.framebuffer;

            if (framebuffer != lastFramebuffer)
            {
                framebuffer->bind();
                lastFramebuffer = framebuffer;
            }

            if (lastShader != shader)
            {
                if (lastShader != nullptr)
                    lastShader->disable();

                shader->use();
                shader->setup(framebuffer);
                lastShader = shader;
            }

            window->clearColor(renderState.clearColor);

            RenderCommand* renderCommand = renderPass->getNextCommand();
            while (renderCommand != nullptr)
            {
                renderCommand->vertexArray->bind();

                auto nextBuffer = renderCommand->buffers;
                ListNode<BufferBinding>* tmp;

                while (nextBuffer != nullptr)
                {
                    nextBuffer->node->buffer->bind(nextBuffer->node->bindTarget);
                    tmp = nextBuffer;
                    nextBuffer = nextBuffer->next;
                    delete tmp;
                }

                updateUniforms(renderState.shader, renderCommand->uniformsState);

                run(renderCommand);

                delete renderCommand;
                renderCommand = renderPass->getNextCommand();
            }

            if (renderState.shouldSwapBuffers)
                window->swapBuffers();

            delete renderPass;
        }
    }

    void BasicRenderer::updateUniforms(Shader* shader, ListNode<UniformState>* uniformsState)
    {
        auto next = uniformsState;

        UniformState* uniformState;
        ListNode<UniformState>* tmp;
        while (next != nullptr)
        {
            uniformState = next->node;
            tmp = next;
            next = next->next;
            delete tmp;

            switch (uniformState->dataType)
            {
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
                // TODO Add more types

            }

            delete uniformState;
        }

        shader->bindDirtyVariables();
    }

    template <typename T>
    void BasicRenderer::updateUniform(Shader* shader, const hash& uniformNameHash, void* value)
    {
        T* castedValue = (T*)(value);
        if (castedValue == nullptr)
            return;

        UniformVariable<T>* uniformVariable = shader->getUniformVariable<T>(uniformNameHash);
        *uniformVariable = *castedValue;
        delete castedValue;

    }
} // namespace blitz