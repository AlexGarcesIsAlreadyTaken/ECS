#ifndef COMPONENT_SQUARE_H
#define COMPONENT_SQUARE_H

#include "Core/Math/Vec3.h"

using namespace Math;

struct Square {
  vec3 vertices[4];

  Square(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
    vertices[3] = v3;
  }
  Square() {
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 0;
    vertices[3] = 0;
  }
};

#endif
