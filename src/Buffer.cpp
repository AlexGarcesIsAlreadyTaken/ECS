#include "glad/glad.h"
#include "Utils/Constants.h"
#include "Core/Renderer/Buffer.h"

void Renderer::initQuad(Renderable& r, Quad& q) {
    glGenVertexArrays(1, &r.vao);
    glBindVertexArray(r.vao);

    Math::vec2 vertices[4] = {
    q.origin,
    Math::vec2(q.origin.x + q.size.x, q.origin.y),
    Math::vec2(q.origin.x, q.origin.y + q.size.y),
    q.origin + q.size
    };

    glGenBuffers(1, &r.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(Real), (void*)0);
    glEnableVertexAttribArray(0);

    uint32_t elements[6] = {0, 1, 2, 1, 2, 3};

    glGenBuffers(1, &r.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void Renderer::renderQuad(Renderable& r, Quad& q) {
  glBindVertexArray(r.vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
