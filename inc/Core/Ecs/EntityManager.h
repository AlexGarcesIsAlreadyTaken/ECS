#ifndef ECS_ENTITY_MANAGER_H
#define ECS_ENTITY_MANAGER_H

#include "Core/Ecs/Names.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>

// Groups: Each group represents the set of entities
// that exactly have those components. When looking for entities
// that have a set of components we check for each group its 
// signature and in case it meets the condition (exactly / atLeast)
// passes all the entities inside them pool
// Problem: max(#groups) = 2^{MAX_COMPONENTS}
typedef std::unordered_set<EntityID> Group;
typedef std::unordered_map<Signature, Group> GroupsPool;

class EntityManager {
public:
  EntityManager();
  ~EntityManager() = default;

  const EntityID createEntity();
  void destroyEntity(EntityID entity);

  const GroupsPool& getGroups() { return this->groupsPool; }

  const Signature getSignature(EntityID entity);
  void setSignature(EntityID entity, const Signature& signature);


private:
  const inline Boolean isAlive(EntityID entity);
  
  std::queue<EntityID> availableEntities;
  
  Signature signatures[MAX_ENTITIES];

  GroupsPool groupsPool;

  uint32_t livingEntities;
};

#endif
