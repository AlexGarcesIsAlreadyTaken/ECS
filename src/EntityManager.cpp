#include "Utils/Logger.h"
#include "Core/Ecs/EntityManager.h"

EntityManager::EntityManager() {
	for (uint32_t i = 0; i < MAX_ENTITIES; ++i) {
		this->availableEntities.push(i);
		this->entitiesStatus[i] = EntityStatus::Dead;
		this->signatures[i].reset();
	}
	this->livingEntities = 0;
  this->mLiveEntities.clear();
}

const EntityID EntityManager::createEntity() {
  DEBUG_MESSAGE("living Entities: " << this->livingEntities);
	LOGGER_ASSERT(this->livingEntities < MAX_ENTITIES, "Too many entities alive.");

	EntityID entity = this->availableEntities.front();
	this->availableEntities.pop();
	this->entitiesStatus[entity] = EntityStatus::Alive;
	this->livingEntities++;
  this->mLiveEntities.insert(entity);
	return entity;
}

void EntityManager::destroyEntity(EntityID entity) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(this->entitiesStatus[entity] != EntityStatus::Dead, "Entity not alive.");
	this->availableEntities.push(entity);
	this->entitiesStatus[entity] = EntityStatus::Dead;
	this->signatures[entity].reset();
	this->livingEntities--;
  this->mLiveEntities.erase(entity);
}

const Signature EntityManager::getSignature(EntityID entity) const {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(this->entitiesStatus[entity] != EntityStatus::Dead, "Entity not alive.");

	return this->signatures[entity];
}

void EntityManager::setSignature(EntityID entity, const Signature& signature) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(this->entitiesStatus[entity] != EntityStatus::Dead, "Entity not alive.");

	this->signatures[entity] = signature;
}

const EntityStatus EntityManager::getStatus(EntityID entity) const {
  return this->entitiesStatus[entity];
}



