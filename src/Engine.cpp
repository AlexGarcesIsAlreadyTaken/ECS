 #include "Core/Engine.h"
#include "Core/Renderer/Texture.h"
#include <time.h>

void Engine::keyReleased(int key) {
	this->keys[key] = false;
}

void Engine::keyPressed(int key) {
	this->keys[key] = true;
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
  this->ecs.registerComponent<TextureComponent>();

  Renderer::Texture texture;
  DEBUG_MESSAGE("plainWhiteTexture address: " << &texture);
  texture = Renderer::createTexture("Textures/plainWhite.png", Renderer::TextureFormat::RGBA);


  srand(time(nullptr));

  for (uint32_t i = 0; i < MAX_ENTITIES; ++i) {
    Entity entity = ecs.createEntity();
    entity.addComponent<Renderable>();
    

    Real x = (rand()%1001)*0.002 - 1.0;
    Real y = (rand()&1001)*0.002 - 1.0;
    Real z = (rand()&1001)*0.002 - 1.0;
    
    entity.addComponent<Quad>(Quad(Math::vec2(x, y), Math::vec2(0.1)));
    
    TextureComponent tC(texture, Math::vec3(x, y, z)/2.0f + 0.5f);
    entity.addComponent<TextureComponent>(tC);
  }

  this->renderSystem.setEcs(&ecs);
  this->renderSystem.init();
}

void Engine::update(Real dt) {
  this->dt = dt;
  this->renderSystem.update(dt);
}

void Engine::render() {
  glClear(GL_COLOR_BUFFER_BIT);
  this->renderSystem.render();
}
