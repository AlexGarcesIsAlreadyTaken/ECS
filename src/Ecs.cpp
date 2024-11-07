#include "Core/Ecs/Ecs.h"


const Entity Ecs::createEntity() {
  return {this->entityManager.createEntity(), this};
}

void Ecs::destroyEntity(EntityID entity) {
  this->entityManager.destroyEntity(entity);
  this->componentManager.entityDestroyed(entity);
}
