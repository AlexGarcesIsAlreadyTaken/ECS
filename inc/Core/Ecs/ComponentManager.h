#ifndef ECS_COMPONENT_MANAGER_H
#define ECS_COMPONENT_MANAGER_H

#include "Core/Ecs/Names.h"
#include "Core/Ecs/ComponentPool.h"
#include <unordered_map>

// Class that handles with all registered components
class ComponentManager {
public:
  ComponentManager();
  ~ComponentManager() = default;

  template <typename T>
  void registerComponent() {
    LOGGER_ASSERT(this->componentsRegistered < MAX_COMPONENTS, "Too many components existing")
    const char* name = typeid(T).name();
    LOGGER_ASSERT(this->componentTypeID.find(name) == this->componentTypeID.end(), "Component already registered.");

    this->componentTypeID.insert({name, this->componentsRegistered});
    this->componentPools[this->componentsRegistered] = std::make_shared<ComponentPool<T>>();

    ++this->componentsRegistered;
  }

  template <typename T>
  void addComponent(EntityID entity, const T& component) {
    getComponentPool<T>()->addComponent(entity, component);
  }

  template <typename T>
  T& getComponent(EntityID entity) const {
    return getComponentPool<T>()->getComponent(entity);
  }

  template <typename T>
  const ComponentType getComponentType() const {
    const char* name = typeid(T).name();
    auto it = this->componentTypeID.find(name);
    LOGGER_ASSERT(it != this->componentTypeID.end(), "Component is not registered.");
    return it->second;
  }
  
  template<typename T>
  void removeComponent(EntityID entity) {
    getComponentPool<T>()->removeData(entity);
  }

	void entityDestroyed(EntityID entity);


private:
  template <typename T>
  std::shared_ptr<ComponentPool<T>> getComponentPool() const {
   const char *name = typeid(T).name();
   auto it = this->componentTypeID.find(name);
   LOGGER_ASSERT(it != this->componentTypeID.end(), "Component not registered.");
   return std::static_pointer_cast<ComponentPool<T>>(this->componentPools[it->second]);
  }
  
  // @brief: map to dynamically store the componentPool inside the array.
  // Also to dynamically update which componentType is assigned to each
  // bit of Signatures
	std::unordered_map<const char*, ComponentType> componentTypeID;
	std::shared_ptr<IComponentPool> componentPools[MAX_COMPONENTS];

	uint32_t componentsRegistered;
  
};

#endif

