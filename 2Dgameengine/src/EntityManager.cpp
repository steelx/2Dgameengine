#include "EntityManager.h"


void EntityManager::Update(float deltaTime)
{
	for (auto& e : entities) {
		e->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (auto& e : entities) {
		e->Render();
	}
}

void EntityManager::ClearData()
{
	for (auto& e : entities) {
		e->Destroy();
	}
}

bool EntityManager::HasNoEntities()
{
	return GetEntityCount() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName)
{
	Entity* entity = new Entity(*this, entityName);
	this->entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return this->entities;
}

unsigned int EntityManager::GetEntityCount()
{
	return this->entities.size();
}
