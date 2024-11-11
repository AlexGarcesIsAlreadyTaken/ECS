 #include "Core/Engine.h"
#include "Core/Renderer/Texture.h"
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
  this->ecs.registerComponent<Quad>();

  Renderer::Texture texture = Renderer::createTexture("Textures/plainWhite.png");

  srand(time(nullptr));

  for (uint32_t i = 0; i < 100; ++i) {
    Entity entity = ecs.createEntity();
    entity.addComponent<Renderable>();
    

    Real x = (rand()%1001)*0.002 - 1.0;
    Real y = (rand()&1001)*0.002 - 1.0;
    
    entity.addComponent<Quad>(Quad(Math::vec2(x, y), Math::vec2(0.1)));
  }

  this->renderSystem.setEcs(&ecs);
  this->renderSystem.init();
}

void Engine::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  this->renderSystem.render();
}
