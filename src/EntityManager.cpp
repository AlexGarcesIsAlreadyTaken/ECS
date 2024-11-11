#include "Utils/Logger.h"
#include "Core/Ecs/EntityManager.h"

EntityManager::EntityManager() {
	for (uint32_t i = 0; i < MAX_ENTITIES; ++i) {
		this->availableEntities.push(i);
		this->signatures[i].reset();
	}
	this->livingEntities = 0;
  this->groupsPool.clear();
}

const EntityID EntityManager::createEntity() {
	LOGGER_ASSERT(this->livingEntities < MAX_ENTITIES, "Too many entities alive.");

	EntityID entity = this->availableEntities.front();
	this->availableEntities.pop();
	this->livingEntities++;
  
  // add entity to
  this->groupsPool[this->signatures[entity]].insert(entity);
	return entity;
}

void EntityManager::destroyEntity(EntityID entity) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(isAlive(entity), "Entity not alive.");
	this->availableEntities.push(entity);
  
  // remove entity from it's group
  this->groupsPool[this->signatures[entity]].erase(entity);
	
  // reset signature
  this->signatures[entity].reset();
	this->livingEntities--;
}

const Signature EntityManager::getSignature(EntityID entity) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(isAlive(entity), "Entity not alive.");

	return this->signatures[entity];
}

void EntityManager::setSignature(EntityID entity, const Signature& signature) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(isAlive(entity), "Entity not alive.");

  this->groupsPool[this->signatures[entity]].erase(entity);
	this->signatures[entity] = signature;
  this->groupsPool[signature].insert(entity);
}

const inline Boolean EntityManager::isAlive(EntityID entity) {
  Signature empty;
  return this->signatures[entity] != empty || groupsPool[empty].find(entity) != groupsPool[empty].end();
}

