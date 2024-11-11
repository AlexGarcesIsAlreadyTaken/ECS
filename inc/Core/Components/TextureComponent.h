#ifndef COMPONENTS_TEXTURE_H
#define COMPONENTS_TEXTURE_H

#include "Core/Math/Vec4.h"
#include "Core/Renderer/Texture.h"

struct TextureComponent {
  Renderer::Texture *texture;
  Math::vec4 tint;

  TextureComponent(Renderer::Texture *texture = nullptr, const Math::vec4& tint = Math::vec4(1.0)) : texture(texture), tint(tint) {}
};

#endif
