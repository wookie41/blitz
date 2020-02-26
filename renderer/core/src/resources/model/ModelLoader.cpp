#include <resources/model/ModelLoader.h>

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <core/Device.h>
#include <core/TextureSampler.h>
#include <core/VertexArray.h>

#include <resources/texture/TextureLoader.h>

extern blitz::Device* BLITZ_DEVICE;

namespace blitz
{

    // position + normal + texture
    constexpr const uint8 SINGLE_VERTEX_DATA_SIZE = 3 * sizeof(float) + 3 * sizeof(float) + 2 * sizeof(float);
    constexpr const uint8 SINGLE_INDEX_DATA_SIZE = sizeof(int);

    constexpr const size_t ASSIMP_3D_VECTOR_SIZE = sizeof(aiVector3D);
    constexpr const size_t ASSIMP_2D_VECTOR_SIZE = sizeof(aiVector2D);

    const char POSITION[] = "position";
    const char NORMALS[] = "normals";
    const char TEXTURE_COORDS[] = "textureCoords";

    Model* ModelLoader::load(const ResourceLocation& location)
    {
        // TODO
        if (location.locationInMemory == nullptr)
        {
            return nullptr;
        }

        const aiScene* scene = nullptr;
        static const auto assimpFlags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;

        blitz::fs::FilePath filePath;
        fs::seperateFileNameAndPath(location.pathToFile, &filePath);

        scene = modelImporter.ReadFile(location.pathToFile, assimpFlags);

        assert(scene != nullptr);

        const auto blitzModel = loadModel(scene->mRootNode, scene, &filePath);
        return blitzModel;
    }

    Model* ModelLoader::loadModel(const aiNode* modelNode, const aiScene* scene, const fs::FilePath* modelPath)
    {
        auto blitzModel = new Model;

        // calculate the amount of space needed for the vertex and element buffers
        uint32 vertexBufferSize = 0;
        uint32 elementBufferSize = 0;

        for (int meshIdx = 0; meshIdx < modelNode->mNumMeshes; ++meshIdx)
        {
            const auto mesh = scene->mMeshes[modelNode->mMeshes[meshIdx]];
            vertexBufferSize += mesh->mNumVertices * SINGLE_VERTEX_DATA_SIZE;
            elementBufferSize += mesh->mNumVertices * SINGLE_INDEX_DATA_SIZE * 3; // 3 because it's triangulated
        }

        if (vertexBufferSize > 0)
        {
            // allocate the data for buffers
            auto vertexData = new char[vertexBufferSize];
            char* elementData = nullptr;

            if (elementBufferSize > 0)
            {
                elementData = new char[vertexBufferSize];
            }

            uint64 totalFacesCount = 0;
            uint64 totalVerticesCount = 0;

            // rewrite the data to the created buffers
            uint64 offsetInVertexData = 0;
            uint64 offsetInElementData = 0;

            for (int meshIdx = 0; meshIdx < modelNode->mNumMeshes; ++meshIdx)
            {
                auto blitzMesh = new Mesh;

                const auto mesh = scene->mMeshes[modelNode->mMeshes[meshIdx]];
                const auto meshMaterial = scene->mMaterials[mesh->mMaterialIndex];

                totalFacesCount += mesh->mNumFaces;
                totalVerticesCount += mesh->mNumVertices;

                blitzMesh->facesCount = mesh->mNumFaces;
                blitzMesh->verticesCount = mesh->mNumVertices;
                loadMaterial(blitzModel, blitzMesh, meshMaterial, modelPath);

                for (int vertexIdx = 0; vertexIdx < mesh->mNumVertices; ++vertexIdx)
                {
                    memcpy(vertexData + offsetInElementData, &mesh->mVertices[vertexIdx], ASSIMP_3D_VECTOR_SIZE);
                    memcpy(vertexData + offsetInElementData + ASSIMP_3D_VECTOR_SIZE, &mesh->mNormals[vertexIdx], ASSIMP_3D_VECTOR_SIZE);

                    // TODO
                    // here we assume that the mesh can have only one set of texture coordinates
                    // add support for multiple textures coordinates if needed in future
                    memcpy(vertexData + offsetInElementData + (ASSIMP_3D_VECTOR_SIZE * 2),
                           &mesh->mTextureCoords[0][vertexIdx], ASSIMP_2D_VECTOR_SIZE);
                    offsetInVertexData += ASSIMP_3D_VECTOR_SIZE * 2 + ASSIMP_3D_VECTOR_SIZE;
                }

                for (unsigned int faceIdx = 0; faceIdx < mesh->mNumFaces; ++faceIdx)
                {
                    const auto indicesSize = mesh->mFaces[faceIdx].mNumIndices * SINGLE_INDEX_DATA_SIZE;
                    if (elementData != nullptr)
                    {
                        memcpy(elementData + offsetInElementData, mesh->mFaces[faceIdx].mIndices, indicesSize);
                        offsetInElementData += indicesSize;
                    }
                }

                blitzModel->meshes.push_back(blitzMesh);
            }

            blitzModel->totalFacesCount = totalFacesCount;
            blitzModel->totalVerticesCount = totalVerticesCount;

            auto vertexBuffer = context.createBuffer(
            { vertexBufferSize, blitz::UsageHint::STATIC, 0, blitz::BindHint::VERTEX, vertexData, false, true });

            auto vertexArray = context.createVertexArray();
            vertexArray->addAttribute({ vertexBuffer, POSITION, blitz::DataType::FLOAT, 3, false, 8 * sizeof(float), 0, 0 });
            vertexArray->addAttribute(
            { vertexBuffer, NORMALS, blitz::DataType::FLOAT, 3, false, 8 * sizeof(float), 3 * sizeof(float), 0 });
            vertexArray->addAttribute(
            { vertexBuffer, TEXTURE_COORDS, blitz::DataType::FLOAT, 2, false, 8 * sizeof(float), 6 * sizeof(float), 0 });

            if (elementData != nullptr)
            {
                auto elementBuffer = context.createBuffer(
                { elementBufferSize, blitz::UsageHint::STATIC, 0, blitz::BindHint::INDEX, vertexData, false, true });
                vertexArray->bindElementBuffer(elementBuffer, DataType::INT);
            }
        }

        for (unsigned int childIdx = 0; childIdx < modelNode->mNumChildren; ++childIdx)
        {
            blitzModel->children.push_back(loadModel(modelNode->mChildren[childIdx], scene, modelPath));
        }

        return blitzModel;
    }

    void ModelLoader::loadMaterial(const Model* model, Mesh* mesh, const aiMaterial* material, const fs::FilePath* modelPath) const
    {
        mesh->diffuseSampler = loadMaterialTexture(model, material, aiTextureType_DIFFUSE, modelPath);
        mesh->specularSampler = loadMaterialTexture(model, material, aiTextureType_SPECULAR, modelPath);
        mesh->normalMapSampler = loadMaterialTexture(model, material, aiTextureType_NORMALS, modelPath);
    }

    TextureSampler*
    ModelLoader::loadMaterialTexture(const Model* model, const aiMaterial* mat, const aiTextureType& type, const fs::FilePath* modelPath) const
    {
        if (mat->GetTextureCount(type) == 0)
        {
            return nullptr;
        }

        aiString textureFilePath;
        mat->GetTexture(type, 0, &textureFilePath);

        char* materialTexturePath = new char[modelPath->directoryPathLength + textureFilePath.length + 1];
        strncpy(materialTexturePath, modelPath->directoryPath, modelPath->directoryPathLength);
        strncpy(materialTexturePath + modelPath->directoryPathLength, textureFilePath.data, textureFilePath.length);
        materialTexturePath[modelPath->directoryPathLength + textureFilePath.length] = '\0';

        ResourceLocation textureLocation{ nullptr, materialTexturePath, 0 };

        // NOTE
        // The thing that will be loading the models before each level (or something similar)
        // will have to unload the resources and delete the textures

        auto texture = textureLoader->loadTexture(textureLocation);
        delete[] materialTexturePath;

        return BLITZ_DEVICE->createSampler(texture);
    }
} // namespace blitz
