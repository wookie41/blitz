#pragma once

#include <core/Precompiled.h>
#include <assimp/Importer.hpp>
#include <resources/model/Model.h>
#include <assimp/material.h>
#include <core/Texture.h>
#include <resources/ResourceLocation.h>

struct aiNode;
struct aiScene;

namespace blitz
{
    class Context;
    class TextureLoader;

    namespace fs
    {
      struct FilePath;
    }

    class ModelLoader
    {
      public:
        ModelLoader(Context& ctx,
                    TextureLoader* tLoader);

        Model* load(const ResourceLocation& location);
        ~ModelLoader() = default;

      private:

        Model* loadModel(const aiNode* modelNode, const aiScene* scene, const fs::FilePath* modelPath);
        void loadMaterial(const Model* model, Mesh* mesh, const aiMaterial* material, const fs::FilePath* modelPath) const;
        TextureSampler* loadMaterialTexture(const Model* model, const aiMaterial *mat, const aiTextureType& type, const fs::FilePath* modelPath) const;

        Context& context;
        Assimp::Importer modelImporter;
        TextureLoader* textureLoader;
    };
} // namespace blitz