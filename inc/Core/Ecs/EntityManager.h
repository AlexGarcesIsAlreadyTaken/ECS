#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "Core/Ecs/Names.h"
#include <queue>

class EntityManager {
public:
  EntityManager();
  ~EntityManager() = default;

  const EntityID createEntity();
  void destroyEntity(EntityID entity);

  const Signature getSignature(EntityID entity) const;
  void setSignature(EntityID entity, const Signature& signature);

  const EntityStatus getStatus(EntityID entity) const;

private:
  std::queue<EntityID> availableEntities;
  EntityStatus entitiesStatus[MAX_ENTITIES];
  Signature signatures[MAX_ENTITIES];

  uint32_t livingEntities;
};

#endif
