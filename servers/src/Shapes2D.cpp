#pragma once

#include <core/Device.h>
#include <core/Context.h>
#include <core/VertexArray.h>
#include <blitzcommon/HashUtils.h>

extern blitz::Device* BLITZ_DEVICE;

namespace blitz
{
    static const char POSITION_ATTR_NAME[] = "_bPosition";
    static const char TEXTURE_COORDS_ATTR_NAME[] = "_bTexCoords";

    // position + texCoords
    static float quadData[] = {
        -1.0f, 1.0f, 0.0f, 1.0f, 
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f, 
        1.0f,  -1.0f, 1.0f, 0.0f,
    };

    VertexArray* quadVertexArray = nullptr;

    void init2DShapes(blitz::Context* context)
    {
        if (quadVertexArray == nullptr)
        {
            Buffer* vertexBuffer =
            context->createBuffer({ sizeof(quadData), blitz::UsageHint::STATIC, blitz::BindHint::VERTEX, quadData, false, true });

            quadVertexArray = context->createVertexArray(2);

            quadVertexArray->addAttribute({ vertexBuffer, blitz::string(POSITION_ATTR_NAME), blitz::DataType::FLOAT, 2,
                                            false, 4 * sizeof(float), 0, 0 });

            quadVertexArray->addAttribute({ vertexBuffer, blitz::string(TEXTURE_COORDS_ATTR_NAME),
                                            blitz::DataType::FLOAT, 2, false, 4 * sizeof(float), 2 * sizeof(float), 0 });
        }
    }
} // namespace blitz::shapes2d