#ifndef ECS_SYSTEMS_RENDER_SYSTEM_H
#define ECS_SYSTEMS_RENDER_SYSTEM_H

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Square.h"
#include "Core/Ecs/BaseSystem.h"

class RenderSystem : public BaseSystem {
public:
  void init() override {
    this->simpleShader = Renderer::createShader("Shaders/simple.vert", "Shaders/simple.frag");
    this->ecs->forEach<Renderable, Square>(Renderer::initSquare);
  }

  void render() override {
    Renderer::useShader(this->simpleShader);
    Renderer::setUniform<Math::vec3>("color", Math::vec3(1.0, 1.0, 0.0));
    this->ecs->forEach<Renderable, Square>(Renderer::renderSquare);
  }
private:
  Renderer::Shader simpleShader;
};

#endif
