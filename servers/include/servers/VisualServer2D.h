#pragma once

#include <blitzcommon/Collections.h>
#include <blitzcommon/DataType.h>
#include <blitzmemory/PoolAllocator.h>
#include <core/RenderCommand.h>
#include <scene/2d/Canvas.h>
#include <scene/2d/Sprite.h>

namespace blitz
{
    struct ViewPort;

    class Framebuffer;

    typedef uint8 CanvasID;
    typedef uint16 SpriteID;

    namespace front
    {
        class RenderingPath;
        class Camera;
    } // namespace front

    // The VisualServer2D is responsible for drawing 2D stuff like sprites to the screen
    // it also (will handle) handles spatial indexing, so we can reduce the number
    // of RenderCommands sent to the backend

    class VisualServer2D
    {
      public:
        void render(Framebuffer* target, const ViewPort* viewPort, const front::Camera* camera, const CanvasID& canvasID) const;

        // TODO add delete canvas method
        CanvasID createCanvas();
        SpriteID createSprite();

        Canvas* getCanvas(const CanvasID& canvasID) const;
        Sprite* getSprite(const SpriteID& spriteID) const;

        void attachToCanvas(const CanvasID& canvasID, CanvasItem* item);
        void detachFromCanvas(const CanvasID& canvasID, CanvasItem* item);

        static VisualServer2D* getInstance();

      private:
        inline void initChildren(CanvasItem* canvasItem) const;

        void renderSprite(Framebuffer* target, const Transform2D& parentTransfrom, const Sprite* sprite, Array<RenderCommand>* commandsBuffer) const;

        // currently we're just drawing everything, but the Array should be
        // replaced with quadtress or something in the future iteration
        Array<Canvas>* canvases;
        Array<Sprite>* sprites;
        memory::PoolAllocator* renderFramePool;
        memory::PoolAllocator* canvasItemsPool;
        front::RenderingPath* renderingPath;
        VisualServer2D(uint8 numCanvases);
        ~VisualServer2D();
    };
} // namespace blitz