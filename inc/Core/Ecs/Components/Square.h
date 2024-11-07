#pragma once

struct Square {
  vec3 vertexs[4];

  Square(vec3 v0, vec3 v1, vec3 v2, vec3 v3) : { vertexs = {v0, v1, v2, v3}; }
};
