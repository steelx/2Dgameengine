#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_syswm.h>
#include <Windows.h>

class Game
{
private:
	bool isRunning;
	unsigned int frameTargetTime;
	SDL_Window* window;
	bool makeWindowTransparent(SDL_Window* window, COLORREF colorKey);

public:
	Game();
	~Game();
	static SDL_Renderer* renderer;
	unsigned int ticksLastFrame;
	bool IsRunning() const;
	void Initialize(int width, int height, unsigned int fps);
	void LoadLevel(int level);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};

