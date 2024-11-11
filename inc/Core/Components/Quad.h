#ifndef COMPONENTS_QUAD_H
#define COMPONENTS_QUAD_H

#include "Core/Math/Vec2.h"

struct Quad {
  Math::vec2 origin;
  Math::vec2 size;

  Quad(const Math::vec2& origin = Math::vec2(0), const Math::vec2& size = Math::vec2(1.0)) : origin(origin), size(size) {}
};

#endif
