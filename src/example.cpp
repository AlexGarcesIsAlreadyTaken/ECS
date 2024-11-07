#include "Core/Ecs/Ecs.h"
#include "Utils/Logger.h"

struct A {};

struct B {};

int main() {
  Ecs ecs;

  ecs.registerComponent<A>();
  ecs.registerComponent<B>();

  Entity a = ecs.createEntity();
  Entity b = ecs.createEntity();

  a.addComponent<A>({});
  a.addComponent<B>({});
  b.addComponent<A>({});
  a.removeComponent<A>();

  a.destroy();
  a.addComponent<A>({});
  
}

