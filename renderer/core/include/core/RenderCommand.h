#pragma once

#include <core/Buffer.h>
#include <core/UniformVariable.h>
#include <core/Precompiled.h>

namespace blitz
{
    class VertexArray;

    struct UniformState
    {
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
        Buffer* buffer;
        BufferBindTarget bindTarget;
    };

    struct RenderCommand
    {
        VertexArray* vertexArray;
        ListNode<BufferBinding>* buffers;
        ListNode<UniformState>* uniformsState;
        DrawMode drawMode;
        PrimitiveType primitiveType;
        int32 startPrimitive;
        int32 numberOfPrimitivesToDraw;
        int32 numberOfIndicesToDraw;
    };
} // namespace blitz