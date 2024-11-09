#ifndef ECS_ECS_H
#define ECS_ECS_H

#include "Core/Ecs/ComponentManager.h"
#include "Core/Ecs/EntityManager.h"
#include "Utils/Logger.h"
#include <functional>
#include <type_traits>

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
  void addComponent(EntityID entity, const T& component = {}) {
    this->componentManager.addComponent<T>(entity, component);
    Signature signature = this->entityManager.getSignature(entity);
    Signature componentSignature = 0b01 << this->componentManager.getComponentType<T>();
    Signature newSignature = signature | componentSignature;
    this->entityManager.setSignature(entity, newSignature);
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
  template <typename ...Types, typename Func>
  void forEach(Func&& function) {
    const Signature maskSignature = getMask<Types...>();
    DEBUG_MESSAGE("Signature: " << maskSignature);
    EntitiesPool entitiesPool = this->entityManager.liveEntities();
    for (auto it = entitiesPool.begin(); it != entitiesPool.end(); it++) {
      const EntityID entity = *it;
      const Signature entitySignature = this->entityManager.getSignature(entity);
      if ((entitySignature&maskSignature) == maskSignature) {
        DEBUG_MESSAGE("Entity(" << entity << ") has components " << entitySignature);
        function(componentManager.getComponent<Types>(entity)...);
      }
    }
  }

private:

  template <typename T, typename ...Types> requires (sizeof...(Types) > 0)
  const Signature getMask() const {
    const ComponentType type = componentManager.getComponentType<T>();
    const Signature typeSignature = 0b01 << type;
    return typeSignature | getMask<Types...>();
  }
  
  template <typename T>
  const Signature getMask() const {
    const ComponentType type = componentManager.getComponentType<T>();
    return 0b01 << type;
  }
  
  EntityManager entityManager;
  ComponentManager componentManager;
};


#endif
