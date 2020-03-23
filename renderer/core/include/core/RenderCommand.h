#pragma once

#include <core/Buffer.h>
#include <core/BufferRange.h>
#include <core/Precompiled.h>
#include <core/UniformVariable.h>

namespace blitz
{
    class VertexArray;

    struct UniformState
    {
        UniformState() {}
        UniformState(const DataType& type, const hash& hash, void* val)
        : dataType(type), uniformNameHash(hash), value(val)
        {
        }

        UniformState& operator=(const UniformState& rhs)
        {
            dataType = rhs.dataType;
            uniformNameHash = rhs.uniformNameHash;
            value = rhs.value;
        }

        DataType dataType;
        hash uniformNameHash;
        void* value;
    };

    enum class DrawMode
    {
        NORMAL,
        INDEXED
    };

    enum class PrimitiveType
    {
        POINTS,
        LINE_STRIP,
        LINE_LOOP,
        LINES,
        LINE_STRIP_ADJACENCY,
        LINES_ADJACENCY,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        TRIANGLES,
        TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY,
        PATCHES
    };

    struct BufferBinding
    {
        BufferRange* bufferRange;
        BufferBindTarget bindTarget;
    };

    class Shader;

    struct RenderCommand
    {
        Shader* shader;
        VertexArray* vertexArray;
        Array<BufferBinding>* buffers;
        Array<UniformState>* uniformsState;
        DrawMode drawMode;
        PrimitiveType primitiveType;
        int32 startVertex;
        int32 startIndex;
        int32 numberOfVerticesToDraw;
        int32 numberOfIndicesToDraw;
    };
} // namespace blitz