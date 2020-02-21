#include <core/Device.h>
#include <core/Logger.h>
#include <core/Renderer.h>
#include <platform/event/SDLEventPooler.h>
#include <platform/input/KeyboardState.h>
#include <platform/input/MouseState.h>
#include <platform/input/SDLInputManager.h>
#include <front/Camera.h>
#include <TestRenderer.h>
#include <front/ForwardRenderingPath.h>

extern blitz::Device* BLITZ_DEVICE;
extern blitz::Renderer* BLITZ_RENDERER;

int wmain(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);

    auto windowDef = blitz::WindowDef{ 0, 0, 400, 400, "test" };
    auto window = BLITZ_DEVICE->createWindow(windowDef);
    window->show();

    window->setClearColor({ 0.5f, 0.0f, 0.5f, 1.0f });
    window->prepare();
    window->swapBuffers();

    blitz::platform::SDLInputManager inputManger;
    blitz::platform::SDLEventPooler pooler{ &inputManger };

    blitz::front::TestRenderer testRenderer{ window };

    blitz::front::Camera camera{ { 0, 0, 2 }, { 0, 0, -1 }, { 0, 1,  0}, 75.f };
    camera.setProjection(blitz::Projection::ORTHOGRAPHIC);

    blitz::front::ForwardRenderingPath renderingPath { &camera, BLITZ_RENDERER, window->getFramebuffer(), testRenderer.getShader() };
    renderingPath.setViewPort({ 0, 0, 400, 400, 0, 100 });

    while (true)
    {
        pooler.poolEvents();

        if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_ESCAPE))
        {
            break;
        }

        if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_W))
        {
            camera.move({0, 0, -1.f});
        }
        
        if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_S))
        {
            camera.move({0, 0, 1.f});
        }

                if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_A))
        {
            camera.move({-1, 0, 0});
        }
        
        if (blitz::platform::isDown(inputManger.getKeyboardState(), blitz::platform::KEY_S))
        {
            camera.move({1, 0, 0});
        }


        window->clearColor();

        renderingPath.addGeometry(testRenderer.render());
        renderingPath.render();

        window->swapBuffers();
    }

    return 0;
}