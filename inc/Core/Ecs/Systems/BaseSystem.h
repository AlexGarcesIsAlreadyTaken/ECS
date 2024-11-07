#ifndef ECS_SYSTEMS_BASE_SYSTEM_H
#define ECS_SYSTEMS_BASE_SYSTEM_H

#include "Core/Math/Constants.h"
#include "Core/Ecs/Ecs.h"

class BaseSystem {
public:
  virtual void setEcs(Ecs *ecs) final { this->ecs = ecs; }

  virtual void init() {}
  virtual void update(Math::Real dt) {}
  virtual void render() {}
protected:
  Ecs *ecs;  
};

#endif
