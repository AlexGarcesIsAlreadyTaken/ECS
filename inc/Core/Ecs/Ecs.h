#ifndef ECS_ECS_H
#define ECS_ECS_H

#include "Core/Ecs/ComponentManager.h"
#include "Core/Ecs/EntityManager.h"
#include <functional>

class Ecs {
public:
  ~Ecs() = default;

  const Entity CreateEntity();
  void destroyEntity();

  template <typename T>
  void registerComponent() {
    this->componentManager.registerComponent<T>();
  }
  
  template <typename T>
  void addComponent(Entity entity, const T& component) {
    this->componentManager.addComponent<T>(entity, component);
    Signature signature = this->entityManager.getSignature(entity);
    Signature componentSignature = 0b01 << this->componentManager.getComponentType<T>();
    this->entityManager.setSignature(entity, signature | componentSignature);
  }

  template <typename T>
  T& getComponent(Entity entity) const {
    return this->componentManager.getComponent<T>(entity);
  }

  template <typename T>
  void removeComponent(Entity entity) {
    this->componentManager.removeComponent<T>(entity);
    Signature signature = this->entityManager.getSignature(entity);
    Signature componentSignature = 0b01 << this->componentManager.getComponentType<T>();
    this->entityManager.setSignature(entity, signature & (~componentSignature));
  }
  
  /*
   * void move(Transform t, Physics p) {
   *   t.x += p.x*dt
   *   t.y += p.y*dt
   * }
   *
   * ecs.forEach<Transform, Physics>(move);
   *
   */

  // TODO: Implement
  template<typename T, typename ...Types>
  void forEach(std::function<void (T, Types...)> function) {
 
  }

private:
  EntityManager entityManager;
  ComponentManager componentManager;
};

#endif
