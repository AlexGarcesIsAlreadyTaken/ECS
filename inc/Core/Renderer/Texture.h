#include "Utils/Constants.h"

namespace Renderer {
  typedef uint32_t Texture;

  // Same logic as with shaders
  // we don't need objects since only
  // one will be used at a time (10 at most)
  namespace {
    Texture currentTexture;
  };

  enum class TextureFormat { RGBA, RGB };

  const Texture createTexture(const char* texturePath, const TextureFormat& format = TextureFormat::RGBA);

};
