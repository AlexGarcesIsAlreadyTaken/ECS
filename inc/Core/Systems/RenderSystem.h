#ifndef ECS_SYSTEMS_RENDER_SYSTEM_H
#define ECS_SYSTEMS_RENDER_SYSTEM_H

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Components/Renderable.h"
#include "Core/Components/Quad.h"
#include "Core/Components/TextureComponent.h"
#include "Core/Ecs/BaseSystem.h"

#include "Utils/Logger.h"

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
private:
  Renderer::Shader simpleShader, textureShader;
};

#endif
