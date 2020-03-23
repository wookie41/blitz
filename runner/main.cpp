#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <core/Texture.h>
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
#include <front/ShadersManager.h>
#include <front/Material.h>

namespace blitz
{
    extern Device* BLITZ_DEVICE;
    extern Renderer* BLITZ_RENDERER;

    void init2DShapes(Context* context);
} // namespace blitz

constexpr const auto TIME_PER_FRAME = 1.f / 60.f;

static char DEFAULT_2D_SHADER_NAME[] = "default2Dshader";
static char DEFAULT_2D_VERTEX_SHADER_PATH[] = "shaders/default2dVert.glsl";
static char DEFAULT_2D_FRAGMENT_SHADER_PATH[] = "shaders/default2dFrag.glsl";

int main(int argc, char** argv)
{
    blitz::Logger::init(argc, argv);

    auto windowDef = blitz::WindowDef{ 0, 0, 800, 600, "test" };
    auto window = blitz::BLITZ_DEVICE->createWindow(windowDef);


    blitz::front::ShadersManager shadersManager;

    blitz::hash default2DShaderName = blitz::hashString(DEFAULT_2D_SHADER_NAME);
    blitz::front::ShadersPaths default2DShaderPaths{ blitz::string(DEFAULT_2D_VERTEX_SHADER_PATH), blitz::string(""),
                                                     blitz::string(DEFAULT_2D_FRAGMENT_SHADER_PATH) };

    blitz::Shader* default2DShader = shadersManager.createShader(default2DShaderName, default2DShaderPaths);

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

    char runSpriteSheetPath[] = "sprite.png";
    blitz::Texture* runSpriteSheetTexture = blitz::loadTexture({ nullptr, runSpriteSheetPath });

    blitz::VisualServer2D* visualServer2D = blitz::VisualServer2D::getInstance();
    blitz::CanvasID canvasID = visualServer2D->createCanvas();
    blitz::SpriteID runSpriteID = visualServer2D->createSprite();
    blitz::Sprite* runSprite = visualServer2D->getSprite(runSpriteID);

    int spriteColCount = 8;
    int spriteRowCount = 1;

    runSprite->texture = runSpriteSheetTexture;
    runSprite->texRegionSize = { runSpriteSheetTexture->getSize().x / spriteColCount, runSpriteSheetTexture->getSize().y / 2 };
    runSprite->texRegionIndex = { 0, 0 };
    runSprite->spriteSize = runSprite->texRegionSize;
    runSprite->transform.translate = { 0, 0 };
    runSprite->material = new blitz::Material;
    runSprite->material->shader = default2DShader;
    visualServer2D->attachToCanvas(canvasID, runSprite);

    float deltaTime = 0;
    unsigned int lastUpdateTime = SDL_GetTicks();
    unsigned int currentFrameTime;

    float spriteAcculTime = 0.f;
    float timePerSprite = 0.085f;

    bool isRunning = true;
    while (isRunning)
    {
        currentFrameTime = SDL_GetTicks();
        deltaTime += (currentFrameTime - lastUpdateTime) / 1000.f;
        lastUpdateTime = currentFrameTime;

        pooler.poolEvents();

        while (deltaTime > TIME_PER_FRAME)
        {
            runSprite->transform.translate.x += 60.f * deltaTime;

            deltaTime -= TIME_PER_FRAME;

            spriteAcculTime += TIME_PER_FRAME;
            if (spriteAcculTime > timePerSprite)
            {
                spriteAcculTime = 0;

                if (++runSprite->texRegionIndex.x < spriteColCount)
                {
                    continue;
                }

                runSprite->texRegionIndex.x = 0;

                if (++runSprite->texRegionIndex.y < spriteRowCount)
                {
                    continue;
                }

                runSprite->texRegionIndex.y = 0;
            }


            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_ESCAPE))
            {
                isRunning = false;
                break;
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_W))
            {
                camera.move({ 0.f, 300.f * TIME_PER_FRAME, 0.f });
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_S))
            {
                camera.move({ 0.f, -300.f * TIME_PER_FRAME, 0.f });
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_A))
            {
                camera.move({ -300.f * TIME_PER_FRAME, 0.f, 0.f });
            }

            if (blitz::platform::isDown(inputManager.getKeyboardState(), blitz::platform::KEY_D))
            {
                camera.move({ 300.f * TIME_PER_FRAME, 0.f, 0.f });
            }

            // const blitz::platform::MouseState* mouseState = inputManager.getMouseState();
            // camera.rotate({ mouseState->relativePos.x * .05f, mouseState->relativePos.y * -.05f, 0 });
        }

        window->clearDepth();
        window->clearColor();

        visualServer2D->render(window->getFramebuffer(), &viewPort, &camera, canvasID);

        window->swapBuffers();
    }

    return 0;
}