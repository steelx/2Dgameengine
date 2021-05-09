#pragma once

#include <SDL.h>

#include "../EntityManager.h"
#include "../libs/glm/glm.hpp"
#include "../Game.h"

class TransformComponent: public Component
{
public:
	glm::vec2 velocity;
	glm::vec2 position;
	int width;
	int height;
	int scale;

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(velX, velY);
		width = w;
		height = h;
		scale = s;
	}

	void Initialize() override {}
	void Update(float deltaTime) override {
		// Update the position/velocity
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
	}
	void Render() override {
		SDL_Rect transformRectangle{ (int)position.x, (int)position.y, width, height };

		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::renderer, &transformRectangle);
	}
};
