#pragma once

#include <blitzcommon/Collections.h>
#include <blitzcommon/DataType.h>
#include <scene/2d/Canvas.h>
#include <blitzmemory/PoolAllocator.h>
#include <core/RenderCommand.h>

namespace blitz
{
    struct RenderModel;
    struct SceneItem;
    struct ViewPort;

    class Framebuffer;

    typedef uint8 SceneID;
    typedef uint32 RenderModelID;

    namespace front
    {
        class RenderingPath;
        class Camera;
    } // namespace front


    class VisualServer3D
    {
      public:
        void render(Framebuffer* target, const ViewPort* viewPort, const front::Camera* camera, const SceneID& sceneID) const;

        SceneID createScene();
        RenderModelID createRenderModel();

        Scene* getScene(const SceneID& sceneID) const;
        RenderModel* getRenderModel(const RenderModelID& renderModelID) const;

        void attachToScene(SceneID sceneID, SceneItem* item);
        void detachFromCanvas(CanvasID canvasID, CanvasItem* item);

        static VisualServer2D* getInstance();

      private:
        inline void initChildren(CanvasItem* canvasItem) const;

        void renderSprite(Framebuffer* target, const Transform2D& parentTransfrom, const Sprite* sprite, Array<RenderCommand>* commandsBuffer) const;

        // currently we're just drawing everything, but the Array should be
        // replaced with quadtress or something in the future iteration
        Array<Canvas>* canvases;
        memory::PoolAllocator* renderFramePool;
        front::RenderingPath* renderingPath;
        VisualServer2D(uint8 numCanvases);
        ~VisualServer2D();
    };
} // namespace blitz