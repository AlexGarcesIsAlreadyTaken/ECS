#ifndef ECS_COMPONENT_MANAGER_H
#define ECS_COMPONENT_MANAGER_H

#include "Core/Ecs/Names.h"
#include "Core/Ecs/ComponentPool.h"

class ComponentManager {
public:
	template <typename T>
	void registerComponent();
	
	template <typename T>
	void addComponent(Entity entity, T component);

	template <typename T>
	T& getComponent(Entity entity) const;
	
	template <typename T>
	const ComponentType getComponentType() const;

	template <typename T>
	void removeComponent(Entity entity);

	void entityDestroyed(Entity entity);

private:
	std::unordered_map<const char*, ComponentType> componentTypeID;
	std::shared_ptr<IComponentPool> componentPools[MAX_COMPONENTS];

	uint8_t componentsRegistered;	
};

#endif

