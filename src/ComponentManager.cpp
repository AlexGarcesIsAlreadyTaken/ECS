#include "Core/Ecs/ComponentManager.h"

ComponentManager::ComponentManager() {
  this->componentsRegistered = 0;
}

void ComponentManager::entityDestroyed(Entity entity) {
  for (auto it = this->componentTypeID.begin(); it != this->componentTypeID.end(); ++it) {
    this->componentPools[it->second]->entityDestroyed(entity);
  }
}
