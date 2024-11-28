#ifndef COMPONENTS_TEXTURE_H
#define COMPONENTS_TEXTURE_H

#include "Core/Math/Vec3.h"
#include "Core/Renderer/Texture.h"

struct TextureComponent {
  Renderer::Texture texture;
  Math::vec3 tint;

  TextureComponent(Renderer::Texture texture = 0, const Math::vec3& tint = Math::vec3(1.0)) : texture(texture), tint(tint) {}
};

#endif
