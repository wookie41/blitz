#include <resources/model/AssimpModelLoader.h>

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <core/Device.h>
#include <core/TextureSampler.h>
#include <core/VertexArray.h>

#ifdef WIN32
#include <filesystem>
#else
#include <experimental/filesystem>
#endif

#include <resources/texture/STBImage2DTextureLoader.h>

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

    AssimpModelLoader::AssimpModelLoader(Context& ctx, ResourcesManager<Texture>* tManager, const ResourceLocation& location)
    : context(ctx), texturesManager(tManager), ResourceLoader::ResourceLoader(location)
    {
        // TODO this is not handled while loading from memory
        if (location.pathToFile != nullptr)
        {
#ifdef WIN32
            const auto modelFilePath = std::filesystem::path(location.pathToFile);
#else
            const auto modelFilePath = std::experimental::filesystem::path(location.pathToFile);
#endif

            const auto modelDirectoryPath = modelFilePath.parent_path().string();
            modelFileDirectoryPathLength = modelDirectoryPath.size();
            modelFileDirectoryPath = new char[modelFileDirectoryPathLength + 1];
            strncpy(modelFileDirectoryPath, modelDirectoryPath.c_str(), modelFileDirectoryPathLength);
            modelFileDirectoryPath[modelFileDirectoryPathLength] = '\0';
        }
    }

    Model* AssimpModelLoader::load()
    {
        const aiScene* scene = nullptr;
        static const auto assimpFlags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;

        if (resourceLocation.pathToFile != nullptr)
        {
            scene = modelImporter.ReadFile(resourceLocation.pathToFile, assimpFlags);
        }
        else if (resourceLocation.locationInMemory != nullptr)
        {
            scene = modelImporter.ReadFileFromMemory(resourceLocation.locationInMemory, resourceLocation.sizeInBytes, assimpFlags);
        }

        assert(scene != nullptr);

        return loadModel(scene->mRootNode, scene);
    }


    Model* AssimpModelLoader::loadModel(const aiNode* modelNode, const aiScene* scene)
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
                loadMaterial(blitzModel, blitzMesh, meshMaterial);

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
            blitzModel->children.push_back(loadModel(modelNode->mChildren[childIdx], scene));
        }

        return blitzModel;
    }

    void AssimpModelLoader::loadMaterial(Model* model, Mesh* mesh, const aiMaterial* material) const
    {
        mesh->diffuseSampler = loadMaterialTexture(model, material, aiTextureType_DIFFUSE);
        mesh->specularSampler = loadMaterialTexture(model, material, aiTextureType_SPECULAR);
        mesh->normalMapSampler = loadMaterialTexture(model, material, aiTextureType_NORMALS);
    }

    TextureSampler* AssimpModelLoader::loadMaterialTexture(Model* model, const aiMaterial* mat, const aiTextureType& type) const
    {
        if (mat->GetTextureCount(type) == 0)
        {
            return nullptr;
        }

        aiString textureFilePath;
        mat->GetTexture(type, 0, &textureFilePath);

        char* materialTexturePath = new char[modelFileDirectoryPathLength + 1 + textureFilePath.length + 1];
        strncpy(materialTexturePath, modelFileDirectoryPath, modelFileDirectoryPathLength);
        strncpy(materialTexturePath + modelFileDirectoryPathLength + 1, textureFilePath.data, textureFilePath.length);
        materialTexturePath[modelFileDirectoryPathLength + textureFilePath.length + 1] = '\0';

#ifdef WIN32
        materialTexturePath[modelFileDirectoryPathLength] = '\\';
#else
        materialTexturePath[modelFileDirectoryPathLength] = '/';
#endif //  WIN32

        auto textureLoader = new STBImage2DTextureLoader({ nullptr, materialTexturePath, 0 });
        auto resourceID = texturesManager->loadResource(textureLoader);
        auto textureResourcePtr = texturesManager->getResource(resourceID);

        return BLITZ_DEVICE->createSampler(textureResourcePtr.raw());
    }

    const ResourceID AssimpModelLoader::getID() const { return 0; }
} // namespace blitz
