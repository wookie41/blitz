#include <core/RenderCommand.h>
#include <front/ModelRenderer.h>
#include <resources/model/Model.h>
#include <front/Renderable.h>

namespace blitz::front
{

    static const auto DIFFUSE_SAMPLER_UNIFORM_HASH = hashString("diffuseMap");
    static const auto SPECULAR_SAMPLER_UNIFORM_HASH = hashString("specularMap");
    static const auto NORMAL_SAMPLER_UNIFORM_HASH = hashString("normalMap");

    BasicModelRenderer::BasicModelRenderer(std::vector<Model*>&& models) : modelsToRender(models){};

    Renderable* BasicModelRenderer::render()
    {
        std::vector<RenderCommand*> renderCommands(modelsToRender.size());

        for (const auto modelToRender : modelsToRender)
        {
            const auto renderableModel = render(modelToRender);
            renderCommands.insert(renderCommands.end(), renderableModel->renderCommands.begin(), renderableModel->renderCommands.end());
            delete renderableModel;
        }

        return new Renderable { renderCommands };
    }

    Renderable* BasicModelRenderer::render(const Model* model) const
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

            // TODO handle models without textures, ex. give them a default color, or just allow models to define material as colors

            if (mesh->diffuseSampler != nullptr)
            {
                renderCommand->uniformsState.push_back(
                new UniformState(DataType::SAMPLER2D, DIFFUSE_SAMPLER_UNIFORM_HASH, (void*)&mesh->diffuseSampler));
            }

            if (mesh->specularSampler != nullptr)
            {
                renderCommand->uniformsState.push_back(
                new UniformState(DataType::SAMPLER2D, SPECULAR_SAMPLER_UNIFORM_HASH, (void*)&mesh->specularSampler));
            }

            if (mesh->normalMapSampler != nullptr)
            {
                renderCommand->uniformsState.push_back(
                new UniformState(DataType::SAMPLER2D, NORMAL_SAMPLER_UNIFORM_HASH, (void*)&mesh->normalMapSampler));
            }


            vertiecsDrawn += renderCommand->numberOfVerticesToDraw;
            indiciesDrawn += renderCommand->numberOfIndicesToDraw;
            renderCommands.push_back(renderCommand);
        }

        for (const auto child : model->children)
        {
            const auto renderableChild = render(child);
            renderCommands.insert(renderCommands.end(), renderableChild->renderCommands.begin(), renderableChild->renderCommands.end());
            delete renderableChild;
        }

        return new Renderable { renderCommands };
    }

} // namespace blitz::front