#pragma once

#include <vector>
#include <unordered_map>
#include <core/UniformVariable.h>
#include <core/Buffer.h>

namespace blitz
{
    class VertexArray;

    struct UniformState
    {
        DataType dataType;
        hash uniformNameHash;
        void* value;
    };

    struct RenderCommand
    {
        VertexArray* vertexArray;
        std::unordered_map<Buffer*, BufferBindTarget> buffers;
        std::vector<UniformState> uniformsState;
    };
} // namespace blitz