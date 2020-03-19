#include <front/ForwardRenderingPath.h>
#include <core/BasicRenderPass.h>
#include <core/Renderer.h>
#include <core/Shader.h>
#include <front/Camera.h>
#include <front/Camera.h>

namespace blitz::front
{
    const auto viewPortSizeUniformName = hashString("_bViewPortSize");
    const auto viewMatrixUniformName = hashString("_bView");
    const auto projectionMatrixUniformName = hashString("_bProjection");

    ForwardRenderingPath::ForwardRenderingPath(Renderer* renderer, Shader* shaderToUse)
    : RenderingPath(renderer), shader(shaderToUse)
    {
    }

    void ForwardRenderingPath::render(RenderList* renderList)
    {
        const Camera* camera = renderList->camera;
        const ViewPort* viewPort = renderList->viewPort;
        Vector2i viewPortSize = { viewPort->width - viewPort->x, viewPort->height - viewPort->y };

        Matrix4f viewMatrix = camera->calculateViewMatrix();

        // TODO this changes only when viewPort changes, we should use this fact
        auto projectionMatrix = calculateProjectionMatrix(viewPort, camera->getProjection(), camera->getFieldOfView());
        
        Array<UniformState> renderPassWideUniform(3);
        renderPassWideUniform.add({ DataType::VECTOR2I, viewPortSizeUniformName, &viewPortSize });
        renderPassWideUniform.add({ DataType::MATRIX4F, viewMatrixUniformName, &viewMatrix });
        renderPassWideUniform.add({ DataType::MATRIX4F, projectionMatrixUniformName, &projectionMatrix });

        RenderState renderState{
            viewPort, camera->getProjection(), true, false, true, shader, renderList->framebuffer, &renderPassWideUniform
        };
        BasicRenderPass forwardRenderPass{ &renderState, renderList->geometry };

        forwardRenderPass.prepare();

        backend->issue(&forwardRenderPass);
        backend->render();
    }
} // namespace blitz::front