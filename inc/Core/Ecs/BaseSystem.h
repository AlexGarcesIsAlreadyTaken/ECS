#ifndef ECS_BASE_SYSTEM_H
#define ECS_BASE_SYSTEM_H

class BaseSystem {
  virtual void init() {} 
  virtual void update(Real dt) {}
  virtual void render() {}
}

#endif
