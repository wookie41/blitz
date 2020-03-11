#ifndef BLITZ_MODEL_H
#define BLITZ_MODEL_H

#include <core/Precompiled.h>

namespace blitz
{
    class VertexArray;
    class TextureSampler;

    struct Mesh
    {
        uint64 facesCount;
        uint64 verticesCount;
        TextureSampler* diffuseSampler;
        TextureSampler* specularSampler;
        TextureSampler* normalMapSampler;
    };

    struct Model
    {
        uint8 verticesInFace;
        uint64 totalFacesCount;
        uint64 totalVerticesCount;
        VertexArray* vertexArray;
        Array<Mesh>* meshes;
        Array<Model*>* children;
        uint32 totalNodesCount; //includes children of children...
    };
}

#endif //BLITZ_MODEL_H
