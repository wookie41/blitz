#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <TestRenderer.h>
#include <core/Device.h>
#include <core/Logger.h>
#include <core/Renderer.h>
#include <front/Camera.h>
#include <front/ForwardRenderingPath.h>
#include <platform/event/SDLEventPooler.h>
#include <platform/input/KeyboardState.h>
#include <platform/input/MouseState.h>
#include <platform/input/SDLInputManager.h>
#include <resources/texture/TextureLoader.h>
#include <servers/VisualServer2D.h>
#include <scene/2d/Sprite.h>


namespace blitz
{
    extern Device* BLITZ_DEVICE;
    extern Renderer* BLITZ_RENDERER;

    void init2DShapes(Context* context);
} // namespace blitz

constexpr const auto TIME_PER_FRAME = 1.f / 60.f;

int wmain(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);

    auto windowDef = blitz::WindowDef{ 0, 0, 800, 600, "test" };
    auto window = blitz::BLITZ_DEVICE->createWindow(windowDef);

    blitz::init2DShapes(&window->getContext());

    window->show();

    window->setClearColor({ 0.5f, 0.0f, 0.5f, 1.0f });
    window->prepare();
    window->swapBuffers();

    blitz::platform::SDLInputManager inputManager;
    blitz::platform::SDLEventPooler pooler{ &inputManager };

    blitz::front::Camera camera{ { 0, 0, 1 }, { 0, 0, -1 }, { 0, 1, 0 }, 75.f };
    camera.setProjection(blitz::Projection::ORTHOGRAPHIC);

    blitz::ViewPort viewPort{ 0, 0, 800, 800, .1f, 100.f };

    char textureLocation[] = "container.jpg";
    blitz::Texture* spriteTex = blitz::loadTexture({ nullptr, textureLocation });

    blitz::VisualServer2D* visualServer2D = blitz::VisualServer2D::getInstance();
    blitz::CanvasID canvasID = visualServer2D->createCanvas();
    blitz::Sprite* sprite = visualServer2D->createSprite();

    sprite->texture = spriteTex;
    sprite->texRegionSize = { spriteTex->getSize().x/4, spriteTex->getSize().y/4 };
    sprite->texRegionIndex = { 1, 1 };
    sprite->spriteSize = { 64, 54 };
    sprite->transform.translate = { 400,  300 };

    visualServer2D->attachToCanvas(canvasID, sprite);

    float deltaTime = 0;
    unsigned int lastUpdateTime = SDL_GetTicks();
    unsigned int currentFrameTime;

    bool isRunning = true;
    while (isRunning)
    {
        currentFrameTime = SDL_GetTicks();
        deltaTime += (currentFrameTime - lastUpdateTime) / 1000.f;
        lastUpdateTime = currentFrameTime;

        pooler.poolEvents();

        while (deltaTime > TIME_PER_FRAME)
        {
            deltaTime -= TIME_PER_FRAME;

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_ESCAPE))
            {
                isRunning = false;
                break;
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_W))
            {
                camera.move(camera.getDirection() * TIME_PER_FRAME * 10);
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_S))
            {
                camera.move(-camera.getDirection() * TIME_PER_FRAME * 10);
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_A))
            {
                camera.move(-camera.calculateRightVector() * TIME_PER_FRAME * 10);
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_D))
            {
                camera.move(camera.calculateRightVector() * TIME_PER_FRAME * 10);
            }


            const blitz::platform::MouseState* mouseState = inputManager.getMouseState();
            camera.rotate({ mouseState->relativePos.x * .05f, mouseState->relativePos.y * -.05f, 0 });
        }

        window->clearDepth();
        window->clearColor();

        visualServer2D->render(window->getFramebuffer(), &viewPort, &camera, canvasID);

        window->swapBuffers();
    }

    return 0;
}