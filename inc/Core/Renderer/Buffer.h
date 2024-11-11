#ifndef RENDERER_BUFFER_H
#define RENDERER_BUFFER_H

#include "Core/Components/Renderable.h"
#include "Core/Components/Quad.h"

namespace Renderer {
  void initQuad(Renderable& r, Quad& q);
  void renderQuad(Renderable& r, Quad& q);
};

#endif
