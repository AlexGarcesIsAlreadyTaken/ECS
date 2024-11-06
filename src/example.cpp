#include "Core/Ecs/EntityManager.h"
#include "Core/Ecs/ComponentManager.h"
#include "Utils/Logger.h"

struct A {};

struct B {};

int main() {
	EntityManager eM;
	ComponentManager cM;

  cM.registerComponent<A>();
  cM.registerComponent<B>();

	Entity a = eM.createEntity();
	Entity b = eM.createEntity();
	Entity c = eM.createEntity();
	Entity d = eM.createEntity();
  
	cM.addComponent<A>(a, {});
	cM.addComponent<A>(b, {});
	cM.addComponent<A>(c, {});
	cM.addComponent<A>(d, {});

  cM.removeComponent<A>(b);
  cM.removeComponent<A>(c);

}

