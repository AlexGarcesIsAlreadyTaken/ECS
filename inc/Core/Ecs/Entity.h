#ifndef ECS_ENTITY_H  
#define ECS_ENTITY_H  

#include "Core/Ecs/Ecs.h"


// There exists to approach when calling to ecs methods
// 1:
//   Entity e = ecs.createEntity();
//   C component;
//   ecs.addComponent<C>(e, component);
// 2:
//  Entity e = ecs.createEntity();
//  C component;
//  e.addComponent<C>(component);
// 
// This example is small so it is not appreciated
// but for enormous code is easier for the user
// to, instead of calling to the ECS, calling from
// the entity, as if it was some kind of living 'Entity'
// There exists to approach when calling to ecs methods
// 1:
//   Entity e = ecs.createEntity();
//   C component;
//   ecs.addComponent<C>(e, component);
// 2:
//  Entity e = ecs.createEntity();
//  C component;
//  e.addComponent<C>(component);
// 
// This example is small so it is not appreciated
// but for enormous code is easier for the user
// to, instead of calling to the ECS, calling from
// the entity, as if it was some kind of living 'Entity'

struct Entity {
  EntityID entity;
  Ecs *ecs;

  template <typename T>
  inline void addComponent(const T& t = {}) {
    ecs->addComponent<T>(this->entity, t);
  }

  template <typename T>
  inline T& getComponent() const {
    return ecs->getComponent<T>(this->entity);
  }

  template <typename T>
  inline void removeComponent() {
    ecs->removeComponent<T>(this->entity);
  }

  inline void destroy() {
    ecs->destroyEntity(this->entity);
  }
};

#endif
