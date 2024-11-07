#include "Core/Ecs/Ecs.h"
#include "Utils/Logger.h"
#include "Core/Ecs/Entity.h"

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

void foo(A a, B b) {
  a.i += b.j;
}

void foo2(B b) {
  b.j++;
}

int main() {
  Ecs ecs;

  ecs.registerComponent<A>();
  ecs.registerComponent<B>();

  Entity a = ecs.createEntity();
  Entity b = ecs.createEntity();
  Entity c = ecs.createEntity();
  Entity d = ecs.createEntity();

  a.addComponent<A>(A(1));
  a.addComponent<B>(B(2));
  b.addComponent<B>(B());
  c.addComponent<A>(A());
  d.addComponent<A>(A());

  ecs.forEach<B>(foo2);
}

