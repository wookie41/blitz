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

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);

    auto windowDef = blitz::WindowDef{ 0, 0, 800, 600, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    window->show();

    window->setClearColor({ 0.5f, 0.0f, 0.5f, 1.0f });
    window->prepare();
    window->swapBuffers();

    blitz::platform::SDLInputManager inputManger;
    blitz::platform::SDLEventPooler pooler{ &inputManger };

    blitz::front::TestRenderer testRenderer{ window };

    blitz::front::Camera camera{ { 0, 0, 3 }, { 0, 0, -1 }, { 0, 1, 0 }, 75.f };
    camera.setProjection(blitz::Projection::ORTHOGRAPHIC);

    blitz::front::ForwardRenderingPath renderingPath{ &camera, BLITZ_RENDERER, window->getFramebuffer(), testRenderer.getShader() };
    renderingPath.setViewPort({ 0, 0, 800, 600, 0.1f, 100.f });

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

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_ESCAPE))
            {
                isRunning = false;
                break;
            }

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_W))
            {
                camera.move({ 0, 0, -10.f * TIME_PER_FRAME });
            }

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_S))
            {
                camera.move({ 0, 0, 10.f * TIME_PER_FRAME });
            }

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_A))
            {
                camera.move({ -10 * TIME_PER_FRAME, 0, 0 });
            }

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_D))
            {
                camera.move({ 10 * TIME_PER_FRAME, 0, 0 });
            }

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_SPACE))
            {
                camera.move({ 0, 10 * TIME_PER_FRAME, 0 });
            }

            if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_LEFT_CTRL))
            {
                camera.move({ 0, -10 * TIME_PER_FRAME, 0 });
            }
        }

        window->clearDepth();
        window->clearColor();

        renderingPath.addGeometry(testRenderer.render());
        renderingPath.render();

        window->swapBuffers();
    }

    return 0;
}