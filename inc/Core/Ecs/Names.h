#ifndef ECS_NAMES_H
#define ECS_NAMES_H

#include "Utils/Constants.h"
#include <bitset>

// @brief: Identifies an entity of the world
typedef uint32_t Entity;
const uint32_t MAX_ENTITIES = 5000;

// @brief: Identifies which type each component is
typedef uint8_t ComponentType;
const uint8_t MAX_COMPONENTS = 32;

// @brief: Template from which all components should "inherit" (formality)
struct IComponent {};

// @brief: linked to an entity, says which components an entity has
typedef std::bitset<MAX_COMPONENTS> Signature;

#endif
