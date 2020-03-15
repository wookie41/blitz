#include <servers/VisualServer2D.h>

#include <core/Device.h>
#include <core/Renderer.h>
#include <scene/2d/Canvas.h>
#include <scene/2d/Sprite.h>
#include <blitzmemory/Memory.h>
#include <core/RenderCommand.h>
#include <front/ForwardRenderingPath.h>

extern blitz::VertexArray* quadVertexArray;
extern blitz::memory::Allocator* allocator;
extern blitz::Renderer* BLITZ_RENDERER;
extern blitz::Device* BLITZ_DEVICE;

namespace blitz
{
    static const uint8 MAX_CANVAS_COUNT = 255;

    static char DEFAULT_2D_SHADER_NAME[] = "default2Dshader";
    static char DEFAULT_2D_VERTEX_SHADER_PATH[] = "shaders/default2dVert.glsl";
    static char DEFAULT_2D_FRAGMENT_SHADER_PATH[] = "shaders/default2dFrag.glsl";

    VisualServer2D::VisualServer2D(uint8 numCanvases)
    {
        memory::resetAllocator();

        canvases = new Array<Canvas>(numCanvases);

        renderFramePool = new memory::PoolAllocator(4096);
        renderFramePool->init();

        Shader* default2DShader = BLITZ_DEVICE->createShader(
        { blitz::string(DEFAULT_2D_SHADER_NAME), DEFAULT_2D_VERTEX_SHADER_PATH, nullptr, DEFAULT_2D_FRAGMENT_SHADER_PATH });

        renderingPath = new front::ForwardRenderingPath(BLITZ_RENDERER, default2DShader);
    }

    VisualServer2D::~VisualServer2D() { delete canvases; }

    CanvasID VisualServer2D::createCanvas()
    {
        const uint8 canvasID = canvases->getSize();
        assert(canvasID < MAX_CANVAS_COUNT);
        canvases->add({});
        Canvas* canvas = canvases->get(canvasID);
        initChildren(canvas);
        return canvasID;
    }

    Canvas* VisualServer2D::getCanvas(CanvasID canvasID) const
    {
        assert(canvasID < MAX_CANVAS_COUNT);
        return canvases->get(canvasID);
    }

    void VisualServer2D::attachToCanvas(CanvasID canvasID, CanvasItem* item)
    {
        assert(canvasID < canvases->getSize());
        Canvas* canvas = canvases->get(canvasID);
        canvas->childrenTail->child = item;
        canvas->childrenTail->next = new CanvasChild;
        canvas->childrenTail = canvas->childrenTail->next;
    }

    void VisualServer2D::detachFromCanvas(CanvasID canvasID, CanvasItem* item)
    {
        assert(canvasID < canvases->getSize());
        Canvas* canvas = canvases->get(canvasID);

        CanvasChild* prevNode = nullptr;
        CanvasChild* childNode = canvas->children;

        while (childNode != nullptr)
        {
            if (childNode->child == item)
            {
                if (prevNode != nullptr)
                {
                    prevNode->next = childNode->next;
                }
                childNode->child = nullptr;
                childNode->next = nullptr;
                return;
            }

            childNode = childNode->next;
        }
    }

    VisualServer2D* VisualServer2D::getInstance()
    {
        static VisualServer2D visualServer2D(MAX_CANVAS_COUNT);
        return &visualServer2D;
    }

    Sprite* VisualServer2D::createSprite()
    {
        Sprite* sprite = new Sprite;
        initChildren(sprite);
        return sprite;
    }

    void VisualServer2D::initChildren(CanvasItem* canvasItem) const
    {
        canvasItem->children = new CanvasChild;
        canvasItem->childrenTail = canvasItem->children;
    }

    void VisualServer2D::render(
        const Framebuffer* target, 
        const ViewPort* viewPort, 
        const front::Camera* camera, 
        const CanvasID& canvasID) const
    {
        allocator = renderFramePool;

        assert(canvasID < canvases->getSize());

        Canvas* canvas = canvases->get(canvasID);
        CanvasChild* nodeToRender = canvas->children;

        Array<RenderCommand>* renderCanvasCommands = new Array<RenderCommand>(128);

        while (nodeToRender != nullptr)
        {
            switch (nodeToRender->child->getType())
            {
            case CanvasItemType::SPRITE:
                renderSprite(target, canvas->transform, (Sprite*)nodeToRender->child, renderCanvasCommands);
                break;
            }

            nodeToRender = nodeToRender->next;
        }

        front::RenderList* renderList = new front::RenderList;
        renderList->viewPort = viewPort;
        renderList->camera = camera;
        renderList->framebuffer = target;
        renderList->geometry = renderCanvasCommands;
        renderList->lights = nullptr;

        renderingPath->render(renderList);

        memory::resetAllocator();
    }

    void VisualServer2D::renderSprite(const Framebuffer* target,
                                      const Transform2D& parentTransfrom,
                                      const Sprite* sprite,
                                      Array<RenderCommand>* commandsBuffer) const
    {
        static const hash SPRITE_TEXTURE_UNIFORM_HASH = hashString("_bSpriteTexture");
        static const hash SPRITE_POSITION_UNIFORM_HASH = hashString("_bSpritePosition");
        static const hash SPRITE_DIMENSIONS_UNIFORM_HASH = hashString("_bSpriteDimensions");
        static const hash SPRITE_TEXTURE_REGION_UNIFORM_HASH = hashString("_bSpriteTextureRegion");

        commandsBuffer->add({});
        RenderCommand* renderCommand = commandsBuffer->get(commandsBuffer->getSize() - 1);

        renderCommand->buffers = nullptr;
        renderCommand->drawMode = DrawMode::NORMAL;
        renderCommand->numberOfVerticesToDraw = 4;
        renderCommand->numberOfIndicesToDraw = 0;
        renderCommand->primitiveType = PrimitiveType::TRIANGLES;
        renderCommand->vertexArray = quadVertexArray;
        renderCommand->uniformsState = new Array<UniformState>(4);

        Array<UniformState>* uniformsStates = renderCommand->uniformsState;
        uniformsStates->add({ DataType::SAMPLER2D, SPRITE_TEXTURE_UNIFORM_HASH, BLITZ_DEVICE->createSampler(sprite->texture) });
        uniformsStates->add({ DataType::VECTOR2I, SPRITE_TEXTURE_REGION_UNIFORM_HASH, (void*)&sprite->texRegion });
        uniformsStates->add({ DataType::VECTOR2F, SPRITE_POSITION_UNIFORM_HASH, (void*)&sprite->transform.translate });
        uniformsStates->add({ DataType::VECTOR2I, SPRITE_DIMENSIONS_UNIFORM_HASH, (void*)&sprite->size });
    }
} // namespace blitz