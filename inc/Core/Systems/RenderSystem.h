#ifndef ECS_SYSTEMS_RENDER_SYSTEM_H
#define ECS_SYSTEMS_RENDER_SYSTEM_H

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Quad.h"
#include "Core/Components/TextureComponent.h"
#include "Core/Ecs/BaseSystem.h"

#include "Utils/Logger.h"

#include <cmath>

class RenderSystem : public BaseSystem {
public:
  void init() override {
    this->simpleShader = Renderer::createShader("Shaders/simple.vert", "Shaders/simple.frag");
    this->textureShader = Renderer::createShader("Shaders/texture.vert", "Shaders/texture.frag");

    auto initBuffer = [&](EntityID entity, Renderable& r, Quad& q) {
      if (this->ecs->has<TextureComponent>(entity)) {
        Renderer::initTextureQuad(r, q);
      } else {
        Renderer::initQuad(r, q);
      }
    };
    this->ecs->forEach<Renderable, Quad>(initBuffer);
  }

  void render() override {

    auto renderBuffers = [&](EntityID entity, Renderable& r, Quad& q) {
      if (this->ecs->has<TextureComponent>(entity)) {
        TextureComponent& tC = this->ecs->getComponent<TextureComponent>(entity);
        Renderer::useShader(this->textureShader);
        Renderer::setTexture(tC.texture, 0);
        Renderer::setUniform<Renderer::Texture>("texture0", 0);
        Renderer::setUniform<Math::vec3>("tint", tC.tint);
      } else {
        Renderer::useShader(this->simpleShader);
        Renderer::setUniform("color", Math::vec3(1.0, 1.0, 0.0));
      }
      Renderer::renderQuad(r, q);
    };

    this->ecs->forEach<Renderable, Quad>(renderBuffers);
  }

  void update(Real dt) override {
    this->ecs->forEach<TextureComponent>([dt](TextureComponent& tC) {changeTint(dt, tC);});

  }
private:
  Renderer::Shader simpleShader, textureShader;

  static void changeTint(Real dt, TextureComponent& tC) {
      Real x = sin(dt)/100;
      Real y = cos(dt)/100;
      tC.tint += Math::vec3(x, y, 0.0);
      if (tC.tint.x > 1.0) tC.tint.x = 0.0;
      if (tC.tint.y > 1.0) tC.tint.y = 0.0;
      if (tC.tint.z > 1.0) tC.tint.z = 0.0;
  }
};

#endif
