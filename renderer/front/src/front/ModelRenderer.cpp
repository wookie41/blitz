#include <front/ModelRenderer.h>
#include <resources/model/Model.h>

namespace blitz::front
{
    static bool useTex = true;
    static const auto DIFFUSE_SAMPLER_UNIFORM_HASH = hashString("diffuseMap");
    static const auto SPECULAR_SAMPLER_UNIFORM_HASH = hashString("specularMap");
    static const auto NORMAL_SAMPLER_UNIFORM_HASH = hashString("normalMap");

    Array<RenderCommand>* BasicModelRenderer::makeRenderable(const Model* model, Array<RenderCommand>* commandsBuffer)
    {
        Array<RenderCommand>* renderCommands =
        commandsBuffer == nullptr ? new Array<RenderCommand>(model->totalNodesCount) : commandsBuffer;

        int32 indiciesDrawn = 0;
        int32 vertiecsDrawn = 0;
        for (uint32 meshIdx = 0; meshIdx < model->meshes->getSize(); ++meshIdx)
        {
            Mesh* mesh = model->meshes->get(meshIdx);
            RenderCommand renderCommand;
            renderCommand.vertexArray = model->vertexArray;
            renderCommand.drawMode = model->totalFacesCount > 0 ? DrawMode::INDEXED : DrawMode::NORMAL;
            renderCommand.primitiveType = PrimitiveType::TRIANGLES;
            renderCommand.startVertex = vertiecsDrawn;
            renderCommand.startIndex = indiciesDrawn;
            renderCommand.numberOfIndicesToDraw = mesh->facesCount * 3;
            renderCommand.numberOfVerticesToDraw = mesh->verticesCount;
            renderCommand.buffers = nullptr;
            renderCommand.uniformsState = new Array<UniformState>(
            1 + // TODO remove +1 - it's for 'useTexture' uniform
            (mesh->diffuseSampler != nullptr) + (mesh->specularSampler != nullptr) + (mesh->normalMapSampler != nullptr));

            // TODO handle models without textures, ex. give them a default color, or just allow models to define material as colors

            if (mesh->diffuseSampler != nullptr)
            {
                renderCommand.uniformsState->add({ DataType::SAMPLER2D, DIFFUSE_SAMPLER_UNIFORM_HASH, (void*)&mesh->diffuseSampler });
            }

            if (mesh->specularSampler != nullptr)
            {
                renderCommand.uniformsState->add({ DataType::SAMPLER2D, SPECULAR_SAMPLER_UNIFORM_HASH, (void*)&mesh->specularSampler });
            }

            if (mesh->normalMapSampler != nullptr)
            {
                renderCommand.uniformsState->add({ DataType::SAMPLER2D, NORMAL_SAMPLER_UNIFORM_HASH, (void*)&mesh->normalMapSampler });
            }

            renderCommand.uniformsState->add({ blitz::DataType::BOOL, blitz::hashString("useTexture"), (void*)&useTex });

            vertiecsDrawn += renderCommand.numberOfVerticesToDraw;
            indiciesDrawn += renderCommand.numberOfIndicesToDraw;
            renderCommands->add(std::move(renderCommand));
        }

        for (uint32 childIdx = 0; childIdx < model->children->getSize(); ++childIdx)
        {
            makeRenderable(*model->children->get(childIdx), renderCommands);
        }

        return renderCommands;
    }

} // namespace blitz::front