#include "Game.h"

Game::Game(): window(NULL), renderer(NULL) {
    this->ticksLastFrame = 0;
    this->frameTargetTime = 15;
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 10.1f;
float projectileVelY = 10.0f;

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

    isRunning = true;
    return;
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
    // Wait until target time has elapsed
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + frameTargetTime));

    // build delta
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    ticksLastFrame = SDL_GetTicks();

    projectilePosX += projectileVelX * deltaTime;
    projectilePosY += projectileVelY * deltaTime;
}

void Game::Render() {
    // Set background color to magenta and clear screen
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile = {
        (int)projectilePosX,
        (int)projectilePosY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 214, 40, 40, 255);
    SDL_RenderFillRect(renderer, &projectile);

    // Add window transparency (Magenta will be see-through)
    this->makeWindowTransparent(window, RGB(255, 0, 255));
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
    return ::SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}
