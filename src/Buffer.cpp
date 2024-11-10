#include "glad/glad.h"
#include "Utils/Constants.h"
#include "Utils/Logger.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"

void Renderer::initSquare(Renderable& r, Square& s) {
    glGenVertexArrays(1, &r.vao);
    glBindVertexArray(r.vao);

    glGenBuffers(1, &r.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s.vertices), s.vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(Real), (void*)0);
    glEnableVertexAttribArray(0);
    
    uint32_t elements[6] = {0, 1, 2, 1, 2, 3};

    glGenBuffers(1, &r.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
}

void Renderer::renderSquare(Renderable& r, Square& s) {
  glBindVertexArray(r.vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
