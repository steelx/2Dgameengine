#pragma once

#include <string>
#include <vector>
#include "Entity.h"
#include "Component.h"


class EntityManager
{
private:
	std::vector<Entity*> entities;

public:
	void Update(float deltaTime);
	void Render();
	void ClearData();
	bool HasNoEntities();
	Entity& AddEntity(std::string entityName);
	std::vector<Entity*> GetEntities() const;
	unsigned int GetEntityCount();
};
