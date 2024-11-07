#ifndef ECS_SYSTEMS_RENDER_SYSTEM_H
#define ECS_SYSTEMS_RENDER_SYSTEM_H

#include "glad/glad.h"
#include "Core/Ecs/Components/Renderable.h"
#include "Core/Ecs/Components/Square.h"
#include "Core/Ecs/Systems/BaseSystem.h"

class RenderSystem : public BaseSystem {
public:

  void init() override {
    this->ecs->forEach<Renderable, Square>(initBuffers);
  }

  void render() override {}

private:
  static void initBuffers(Renderable& r, Square& s) {
    glGenVertexArrays(1, &r.vao);
    glBindVertexArray(r.vao);

    glGenBuffers(1, &r.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r.vbo);
    glBufferData(0, sizeof(s.vertices), s.vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &r.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r.ebo);
    glBufferData(1, sizeof(elements), elements, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(Real), (void*)0);
    glEnableVertexAttribArray(0);

    DEBUG_MESSAGE("Render System init");
  }

  constexpr static uint8_t elements[6] = {0, 1, 2, 1, 2, 3};
};

#endif
