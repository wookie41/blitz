#ifndef BLITZ_ASSIMPMODELLOADER_H
#define BLITZ_ASSIMPMODELLOADER_H

#include <core/Precompiled.h>
#include <assimp/Importer.hpp>
#include <resources/model/Model.h>
#include <assimp/material.h>
#include <resources/ResourcesManager.h>
#include <core/Texture.h>
#include <resources/ResourceLoader.h>

struct aiNode;
struct aiScene;

namespace blitz
{
    class Context;

    class AssimpModelLoader : public ResourceLoader<Model>
    {
      public:
        AssimpModelLoader(Context& ctx,
                        ResourcesManager<Texture>* tManager,
                        const ResourceLocation& location);

        ~AssimpModelLoader() = default;

        Model* load() override;

        const ResourceID getID() const override;

      private:

        Model* loadModel(const aiNode* modelNode, const aiScene* scene);
        void loadMaterial(Model* model, Mesh* mesh, const aiMaterial* material) const;
        TextureSampler* loadMaterialTexture(Model* model, const aiMaterial *mat, const aiTextureType& type) const;

        ResourceID modelID;
        Assimp::Importer modelImporter;
        Context& context;
        ResourcesManager<Texture>* texturesManager;
        char* modelFileDirectoryPath = nullptr;
        uint32 modelFileDirectoryPathLength = 0;
    };
} // namespace blitz

#endif // BLITZ_ASSIMPMODELLOADER_H
