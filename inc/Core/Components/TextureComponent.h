#include "Core/Math/Vec3.h"

struct TextureComponent {
  Texture texture;
  Math::vec3 tint;

  TextureComponent(texture = nullptr, tint = Math::vec3(1.0, 1.0, 1.0)) : texture(texture), tint(tint) {}
};
