#ifndef ECS_COMPONENT_POOL_H
#define ECS_COMPONENT_POOL_H

#include "Core/Ecs/Names.h"
#include "Utils/Logger.h"
#include <vector>
#include <memory>

class IComponentPool {
public:
	virtual ~IComponentPool() = default;
	virtual void entityDestroyed(EntityID entity) = 0;
};

// Represents a pool of T-Components
template <typename T>
class ComponentPool : public IComponentPool {
public:
	ComponentPool()	{
		for (uint32_t i = 0; i < MAX_ENTITIES; i++) this->sparseSet[i] = NULL_INDEX;
		this->denseSet.resize(0);
		this->componentToEntity.resize(0);
	}

	void addComponent(EntityID entity, const T& component) {
		LOGGER_ASSERT(this->sparseSet[entity] == NULL_INDEX, "entity already has component.");
		LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
		this->sparseSet[entity] = denseSet.size();
		this->denseSet.push_back(component);
		this->componentToEntity.push_back(entity);
	}

	T* getComponent(EntityID entity) {
		LOGGER_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");
		LOGGER_ASSERT(this->sparseSet[entity] != NULL_INDEX, "Entity has no component.")
		return &(this->denseSet[this->sparseSet[entity]]);
	}
	
  void removeData(EntityID entity) {
    LOGGER_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");
    LOGGER_ASSERT(this->sparseSet[entity] != NULL_INDEX, "Removing non-existing entity.");

    size_t aux = this->sparseSet[entity];
	
    // flip last component with the one we are gonna remove
    this->denseSet[aux] = this->denseSet[this->denseSet.size() - 1];
    this->componentToEntity[aux] = this->componentToEntity[this->componentToEntity.size() - 1];

    // update last component's entity pointer
    this->sparseSet[this->componentToEntity[aux]] = aux;	

    // entity points nowhere
    this->sparseSet[entity] = NULL_INDEX;
	
    // remove component (no longer needed)
    this->denseSet.pop_back();
    this->componentToEntity.pop_back();
  }

  void entityDestroyed(EntityID entity) override {
    if (this->sparseSet[entity] != NULL_INDEX) this->removeData(entity);
  }
private:
	// @brief: for each entity, the component(pointer) it has, in case is active
	size_t sparseSet[MAX_ENTITIES];

	// @brief: for each active component, the entity which is using it
	std::vector<size_t> componentToEntity;

	// @brief: the component array itself (packed for data proximity)
	std::vector<T> denseSet;

	static const size_t NULL_INDEX = MAX_ENTITIES;
};

#endif
