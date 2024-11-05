#include "Core/Ecs/ComponentManager.h"

template <typename T>
void ComponentManager::registerComponent<T>() {
	LOGGER_ASSERT(this->componentsRegistered < MAX_COMPONENTS, "Too many components existing")
	const char* name = typeid(T).name();
	LOGGER_ASSERT(this->componentTypeID.find(name) == nullptr, "Component already registered.");

	this->componentTypeID.insert({name, this->componentsRegistered});
	this->componentPools[this->componentsRegistered] = std::make_shared<ComponentPool<T>>();

	++this->componentsRegistered;
}

