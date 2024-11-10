 #include "Core/Engine.h"
#include <time.h>

void Engine::keyReleased(int key) {
	this->keys[key] = false;
}

void Engine::keyPressed(int key) {
	this->keys[key] = true;
}

void Engine::update(float dt) {
	this->dt = dt;
}

const float Engine::deltaTime() const {
	return this->dt;
}

const bool Engine::getKey(int key) const {
	return this->keys[key];
}

void Engine::init() {
  this->ecs.registerComponent<Renderable>();
  this->ecs.registerComponent<Square>();

  srand(time(nullptr));

  for (uint32_t i = 0; i < 10000; ++i) {
    DEBUG_MESSAGE("iteration: " << i);
    Entity entity = ecs.createEntity();
    entity.addComponent<Renderable>();

    Real x = (rand()%1001)*0.002 - 1.0;
    Real y = (rand()&1001)*0.002 - 1.0;
    
    Math::vec3 v0(x, y, 0);
    Math::vec3 v1(x, y + 0.1, 0);
    Math::vec3 v2(x + 0.1, y, 0);
    Math::vec3 v3(x + 0.1, y + 0.1, 0);
    entity.addComponent<Square>(Square(v0, v1, v2, v3));
  }

  this->renderSystem.setEcs(&ecs);
  this->renderSystem.init();
}

void Engine::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  this->renderSystem.render();
}
