#ifndef ECS_SYSTEMS_BASE_SYSTEM_H
#define ECS_SYSTEMS_BASE_SYSTEM_H

#include "Core/Ecs/Ecs.h"
#include "Utils/Constants.h"

class BaseSystem {
public:
  virtual void setEcs(Ecs *ecs) final { this->ecs = ecs; }

  virtual void init() {}
  virtual void update(Real dt) {}
  virtual void render() {}
protected:
  Ecs *ecs;  
};

#endif
