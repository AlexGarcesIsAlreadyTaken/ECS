#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "Core/Ecs/Names.h"
#include <queue>

class EntityManager {
public:
	EntityManager();
~EntityManager() = default;

	const Entity createEntity();
	void destroyEntity(Entity entity);

	const Signature getSignature(Entity entity) const;
	void setSignature(Entity entity, const Signature& signature);


private:
	std::queue<Entity> availableEntities;
	bool entitiesStatus[MAX_ENTITIES];
	Signature signatures[MAX_ENTITIES];

	uint32_t livingEntities;
};

#endif
