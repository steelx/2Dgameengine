#include "Game.h"
#include <iostream>

Game::Game() {
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
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
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
    SDL_SetRenderDrawColor(renderer, 234, 226, 183, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile = {
        (int)projectilePosX,
        (int)projectilePosY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 214, 40, 40, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
