#include <core/RenderCommand.h>
#include <front/ModelRenderer.h>
#include <resources/model/Model.h>

namespace blitz::front
{

    static const auto DIFFUSE_SAMPLER_UNIFORM_HASH = hashString("diffuseMap");
    static const auto SPECULAR_SAMPLER_UNIFORM_HASH = hashString("specularMap");
    static const auto NORMAL_SAMPLER_UNIFORM_HASH = hashString("normalMap");

    BasicModelRenderer::BasicModelRenderer(std::vector<Model*>&& models) : modelsToRender(models){};

    std::vector<RenderCommand*> BasicModelRenderer::produceCommands()
    {
        std::vector<RenderCommand*> renderCommands(modelsToRender.size());

        for (const auto modelToRender : modelsToRender)
        {
            const auto renderModelCommands = createCommandsFor(modelToRender);
            renderCommands.insert(renderCommands.end(), renderModelCommands.begin(), renderModelCommands.end());
        }

        return renderCommands;
    }

    std::vector<RenderCommand*> BasicModelRenderer::createCommandsFor(const Model* model) const
    {
        std::vector<RenderCommand*> renderCommands;

        int32 indiciesDrawn = 0;
        int32 vertiecsDrawn = 0;
        for (const auto mesh : model->meshes)
        {
            auto renderCommand = new RenderCommand{};
            renderCommand->vertexArray = model->vertexArray;
            renderCommand->drawMode = model->totalFacesCount > 0 ? DrawMode::INDEXED : DrawMode::NORMAL;
            renderCommand->primitiveType = PrimitiveType::TRIANGLES;
            renderCommand->startIndex = vertiecsDrawn;
            renderCommand->startIndex = indiciesDrawn;
            renderCommand->numberOfIndicesToDraw = mesh->facesCount * 3;
            renderCommand->numberOfVerticesToDraw = mesh->verticesCount;

            // TODO handle models without textures

            renderCommand->uniformsStates.push_back(
				new UniformState(DataType::SAMPLER2D, DIFFUSE_SAMPLER_UNIFORM_HASH, (void*)&mesh->diffuseSampler)
            );

        	renderCommand->uniformsStates.push_back(
				new UniformState(DataType::SAMPLER2D, SPECULAR_SAMPLER_UNIFORM_HASH, (void*)&mesh->specularSampler)
            );

        	renderCommand->uniformsStates.push_back(
				new UniformState(DataType::SAMPLER2D, NORMAL_SAMPLER_UNIFORM_HASH, (void*)&mesh->normalMapSampler)
            );

            vertiecsDrawn += renderCommand->numberOfVerticesToDraw;
            indiciesDrawn += renderCommand->numberOfIndicesToDraw;
        }

        return renderCommands;
    }

} // namespace blitz::front