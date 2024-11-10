#ifndef RENDERER_BUFFER_H
#define RENDERER_BUFFER_H

#include "Core/Components/Renderable.h"
#include "Core/Components/Square.h"

namespace Renderer {
  void initSquare(Renderable& r, Square& s);
  void renderSquare(Renderable& r, Square& s);
};

#endif
