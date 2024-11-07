#ifndef ECS_ECS_H
#define ECS_ECS_H

#include "Core/Ecs/ComponentManager.h"
#include "Core/Ecs/EntityManager.h"
#include <functional>

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

struct Entity;

class Ecs {
public:
  ~Ecs() = default;

  const Entity createEntity();
  void destroyEntity(EntityID entity);

  template <typename T>
  void registerComponent() {
    this->componentManager.registerComponent<T>();
  }
  
  template <typename T>
  void addComponent(EntityID entity, const T& component) {
    this->componentManager.addComponent<T>(entity, component);
    Signature signature = this->entityManager.getSignature(entity);
    Signature componentSignature = 0b01 << this->componentManager.getComponentType<T>();
    Signature newSignature = signature | componentSignature;
    this->entityManager.setSignature(entity, newSignature);
    DEBUG_MESSAGE(entity << " signature: " << newSignature);
  }

  template <typename T>
  T& getComponent(EntityID entity) const {
    return this->componentManager.getComponent<T>(entity);
  }

  template <typename T>
  void removeComponent(EntityID entity) {
    this->componentManager.removeComponent<T>(entity);
    Signature signature = this->entityManager.getSignature(entity);
    Signature componentSignature = 0b01 << this->componentManager.getComponentType<T>();
    Signature newSignature = signature & (~componentSignature);
    this->entityManager.setSignature(entity, newSignature);
    DEBUG_MESSAGE(entity << " signature: " << newSignature);
  }
  
  /*
   * void move(Transform t, Physics p) {
   *   t.x += p.x*dt
   *   t.y += p.y*dt
   * }
   *
   * ecs.forEach<Transform, Physics>(move);
   *
   * forEach<Transform, Physics>(move) {
   *   A(entity in entities) {
   *     if entities has {Transform, Physics}: move();
   *   }
   * }
   */

  // @brief: For each entity with components {T, Types...}
  // we execute method "function" taking the mentioned components
  // as arguments ("function" is a void method)
  template<typename ...Types>
  void forEach(const std::function<void(Types&...)>& function) {
 
  }

private:
  EntityManager entityManager;
  ComponentManager componentManager;
};

struct Entity {
  EntityID entity;
  Ecs *ecs;

  template <typename T>
  inline void addComponent(const T& t) {
    ecs->addComponent<T>(this->entity, t);
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
