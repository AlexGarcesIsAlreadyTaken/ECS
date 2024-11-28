#ifndef RENDERER_TEXTURE__H
#define RENDERER_TEXTURE__H

#include "Utils/Constants.h"

namespace Renderer {
  typedef uint32_t Texture;

  enum class TextureFormat { RGBA, RGB };

  const Texture createTexture(const char* texturePath, const TextureFormat& format = TextureFormat::RGBA);

  void setTexture(Texture texture, uint8_t textureID = 0);

};

#endif
