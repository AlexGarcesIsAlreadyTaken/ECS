#include "Utils/Logger.h"
#include "Core/Ecs/EntityManager.h"

EntityManager::EntityManager() {
	for (uint32_t i = 0; i < MAX_ENTITIES; ++i) {
		this->availableEntities.push(i);
		this->entitiesStatus[i] = false;
		this->signatures[i].reset();
	}
	this->livingEntities = 0;
}

const Entity EntityManager::createEntity() {
	LOGGER_ASSERT(this->livingEntities < MAX_ENTITIES, "Too many entities alive.");

	Entity entity = this->availableEntities.front();
	this->availableEntities.pop();
	this->entitiesStatus[entity] = true;
	this->livingEntities++;
	return entity;
}

void EntityManager::destroyEntity(Entity entity) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(this->entitiesStatus[entity], "Entity not alive.");
	this->availableEntities.push(entity);
	this->entitiesStatus[entity] = false;
	this->signatures[entity].reset();
	--this->livingEntities;
}

const Signature EntityManager::getSignature(Entity entity) const {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(this->entitiesStatus[entity], "Entity not alive.");

	return this->signatures[entity];
}

void EntityManager::setSignature(Entity entity, const Signature& signature) {
	LOGGER_ASSERT(entity < MAX_ENTITIES, "entity out of range.");
	LOGGER_ASSERT(this->entitiesStatus[entity], "Entity not alive.");

	this->signatures[entity] = signature;
}





