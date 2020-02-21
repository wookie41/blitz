#include <core/BasicRenderPass.h>
#include <core/Framebuffer.h>
#include <core/Renderer.h>
#include <core/Shader.h>
#include <front/Camera.h>
#include <front/ForwardRenderingPath.h>
#include <front/Renderable.h>


namespace blitz::front
{
    const auto viewMatrixUniformName = hashString("_bView");
    const auto projectionMatrixUniformName = hashString("_bProjection");

    ForwardRenderingPath::ForwardRenderingPath(Camera* cameraToRenderFrom, blitz::Renderer* renderer, Framebuffer* targetFrameBuffer, Shader* shaderToUse)
    : RenderingPath(cameraToRenderFrom, renderer), framebuffer(targetFrameBuffer), shader(shaderToUse)
    {
    }

    void ForwardRenderingPath::render()
    {
        auto viewMatrix = camera->calculateViewMatrix();
        auto projectionMatrix = calculateProjectionMatrix(camera->getProjection(), camera->getFieldOfView());

        auto viewMatrixUniformState = new UniformState{ DataType::MATRIX4F, viewMatrixUniformName, &viewMatrix };
        auto projectionMatrixUniformState = new UniformState{ DataType::MATRIX4F, projectionMatrixUniformName, &projectionMatrix };

        std::vector<UniformState*> forwardRenderingPathUniforms;
        forwardRenderingPathUniforms.push_back(viewMatrixUniformState);
        // forwardRenderingPathUniforms.push_back(projectionMatrixUniformState);

        auto renderState = new RenderState{ viewPort,    camera->getProjection(),     true, true, shader,
                                            framebuffer, forwardRenderingPathUniforms };

        blitz::RenderPass* forwardRenderPass = new blitz::BasicRenderPass(renderState);

        for (const auto geometry : geometryToRender)
        {
            for (const auto command : geometry->renderCommands)
            {
                forwardRenderPass->add(command);
            }
        }

        geometryToRender.clear();

        // TODO add UI, Lights

        forwardRenderPass->finish();

        backendRenderer->issue(forwardRenderPass);
        backendRenderer->render();
    }

    void ForwardRenderingPath::addGeometry(Renderable* geometry) { geometryToRender.push_back(geometry); }

    void ForwardRenderingPath::addUIElement(Renderable* uiElement) { uiElementsToRender.push_back(uiElement); }

    void ForwardRenderingPath::addLight(Light* light) { lights.push_back(light); }
} // namespace blitz::front