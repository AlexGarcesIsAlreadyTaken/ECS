 #include "Core/Engine.h"

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

  this->entity = ecs.createEntity();
  this->entity.addComponent<Renderable>();
  Math::vec3 v0(-0.5, -0.5, 0);
  Math::vec3 v1(-0.5, 0.5, 0);
  Math::vec3 v2(0.5, -0.5, 0);
  Math::vec3 v3(0.5, 0.5, 0);
  this->entity.addComponent<Square>(Square(v0, v1, v2, v3));

  this->renderSystem.setEcs(&ecs);
  this->renderSystem.init();
}

void Engine::render() {
  this->renderSystem.render();
}
