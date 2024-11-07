#include "Core/Ecs/Ecs.h"
#include "Utils/Logger.h"
#include "Core/Ecs/Entity.h"
#include "Core/Ecs/Systems/BaseSystem.h"

struct A {
  uint8_t i;
  A() : i(0) {}
  A(uint8_t i) : i(i) {}
};

struct B {
  uint8_t j;
  B() : j(0) {}
  B(uint8_t j) : j(j) {}
};

int main() {
  Ecs ecs;

  ecs.registerComponent<A>();
  ecs.registerComponent<B>();

  Entity a = ecs.createEntity();
  Entity b = ecs.createEntity();
  Entity c = ecs.createEntity();
  Entity d = ecs.createEntity();

  B aB = B(2);

  a.addComponent<A>(A(1));
  a.addComponent<B>(aB);
  b.addComponent<B>();
  c.addComponent<A>();
  d.addComponent<A>();

  BaseSystem system = ecs.registerSystem<BaseSystem>();

}

