#pragma once

#include <vector>
#include <string>

#include "EntityManager.h"
#include "Component.h"

class EntityManager;
class Component;

class Entity {
private:
	const EntityManager& manager;
	bool isActive;
	std::vector<Component*> components;

public:
	std::string name;
	Entity(EntityManager& manager);
	Entity(EntityManager& manager, std::string name);
	void Update(float detltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;

	template <typename T, typename... Targs>
	T& AddComponent(Targs&&... args) {
		// make sure T implements Component class
		T* newComponent{ new T(std::forward<Targs>(args)...) };
		newComponent->owner = this;
		components.emplace_back(newComponent);
		newComponent->Initialize();
		return *newComponent;
	}
};
