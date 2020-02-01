#include <core/ogl/BasicOpenGLRenderer.h>
#include <core/ogl/OpenGLDataType.h>
#include <core/VertexArray.h>

namespace blitz::ogl
{
    void BasicOpenGLRenderer::run(RenderCommand* renderCommand)
    {
        GLenum glPrimitiveType = mapToGLType(renderCommand->primitiveType);
        switch (renderCommand->drawMode)
        {
        case DrawMode::NORMAL:
            glDrawArrays(glPrimitiveType, renderCommand->startPrimitive, renderCommand->numberOfPrimitivesToDraw);
            break;
        case DrawMode::INDEXED:
            glDrawElements(glPrimitiveType, renderCommand->numberOfIndicesToDraw,
                           mapToGLDataType(renderCommand->vertexArray->getIndicesType()), 0);
            break;
        }
    }

    unsigned int BasicOpenGLRenderer::mapToGLType(const PrimitiveType& type)
    {
        switch (type)
        {
        case PrimitiveType::POINTS:
            return GL_POINTS;
        case PrimitiveType::LINE_STRIP:
            return GL_LINE_STRIP;
        case PrimitiveType::LINE_LOOP:
            return GL_LINE_LOOP;
        case PrimitiveType::LINES:
            return GL_LINES;
        case PrimitiveType::LINE_STRIP_ADJACENCY:
            return GL_LINE_STRIP_ADJACENCY;
        case PrimitiveType::LINES_ADJACENCY:
            return GL_LINES_ADJACENCY;
        case PrimitiveType::TRIANGLE_STRIP:
            return GL_TRIANGLE_STRIP;
        case PrimitiveType::TRIANGLE_FAN:
            return GL_TRIANGLE_FAN;
        case PrimitiveType::TRIANGLES:
            return GL_TRIANGLES;
        case PrimitiveType::TRIANGLE_STRIP_ADJACENCY:
            return GL_TRIANGLE_STRIP_ADJACENCY;
        case PrimitiveType::TRIANGLES_ADJACENCY:
            return GL_TRIANGLES_ADJACENCY;
        case PrimitiveType::PATCHES:
            return GL_PATCHES;
        default:
            assert(false);
            return 0;
        }
    }

    void BasicOpenGLRenderer::setViewPort(const ViewPort* viewPort)
    {
        glViewport(viewPort->x, viewPort->y, viewPort->width, viewPort->height);
    }
} // namespace blitz::ogl