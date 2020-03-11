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

extern blitz::Device* BLITZ_DEVICE;
extern blitz::Renderer* BLITZ_RENDERER;

constexpr const auto TIME_PER_FRAME = 1.f / 60.f;

int wmain(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);

    auto windowDef = blitz::WindowDef{ 0, 0, 800, 600, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    window->show();

    window->setClearColor({ 0.5f, 0.0f, 0.5f, 1.0f });
    window->prepare();
    window->swapBuffers();

    blitz::platform::SDLInputManager inputManager;
    blitz::platform::SDLEventPooler pooler{ &inputManager };

    blitz::front::Camera camera{ { 0, 0, 1 }, { 0, 0, -1 }, { 0, 1, 0 }, 75.f };
    camera.setProjection(blitz::Projection::PERSPECTIVE);

    blitz::front::TestRenderer testRenderer{ window, &camera, {0, 0, 800, 800, .1f, 100.f} };

    blitz::front::ForwardRenderingPath renderingPath{ BLITZ_RENDERER, testRenderer.getShader() };

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

        renderingPath.render(testRenderer.getTestRenderList());

        window->swapBuffers();
    }

    return 0;
}