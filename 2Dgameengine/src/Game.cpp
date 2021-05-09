#include "Game.h"
// TransformComponent has EntityManager
#include "components/TransformComponent.h"
#include "../libs/glm/glm.hpp"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game(): window(NULL) {
    this->ticksLastFrame = 0;
    this->frameTargetTime = 15;
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height, unsigned int fps) {
    frameTargetTime = fps;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        "SDL Game C++",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int level)
{
    // Add Entity and Component to entities
    Entity& projectile{ manager.AddEntity("projectile") };
    projectile.AddComponent<TransformComponent>(0,0,5,5,32,32,1);

}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT: {
        isRunning = false;
        break;
    }
    case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
        }
    }
    }
}

void Game::Update() {
    // wait time
    auto timeToWait = frameTargetTime - (SDL_GetTicks() - ticksLastFrame);

    // Wait until target time has elapsed
    if (timeToWait > 0 && timeToWait <= frameTargetTime) SDL_Delay(timeToWait);

    // build delta
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    // clamp
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    // here we call the manager.update to update all Entities, passing deltaTime
    manager.Update(deltaTime);
}

void Game::Render() {
    // 01 Set background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // 02 clear the back buffer
    SDL_RenderClear(renderer);

    // here we call the manager.render to render all Entities
    if (manager.HasNoEntities()) return;
    manager.Render();

    // Add window transparency (same color as background see-through)
    //this->makeWindowTransparent(window, RGB(0, 0, 0));

    // 03 swap front & back buffers
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Makes a window transparent by setting a transparency color.
// https://stackoverflow.com/a/51956224/942317
bool Game::makeWindowTransparent(SDL_Window* window, COLORREF colorKey) {
    // Get window handle (https://stackoverflow.com/a/24118145/3357935)
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    // Change window type to layered (https://stackoverflow.com/a/3970218/3357935)
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Set transparency color
    // colorKey must be similar to Renderer clear color
    return ::SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}
