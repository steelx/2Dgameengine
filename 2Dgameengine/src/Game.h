#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game
{
private:
	bool isRunning;
	unsigned int frameTargetTime;
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Game();
	~Game();
	unsigned int ticksLastFrame;
	bool IsRunning() const;
	void Initialize(int width, int height, unsigned int fps);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

