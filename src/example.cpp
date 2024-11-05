#include "Core/Ecs/EntityManager.h"
#include "Core/Ecs/ComponentPool.h"

struct A {};

int main() {
	EntityManager eM;
	ComponentPool<A> cP;


	Entity A = eM.createEntity();
	Entity B = eM.createEntity();
	Entity C = eM.createEntity();
	Entity D = eM.createEntity();

	cP.addComponent(A, {});
	cP.addComponent(B, {});
	cP.addComponent(C, {});
	cP.addComponent(D, {});

	cP.removeData(B);
}

