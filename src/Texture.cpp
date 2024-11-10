#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Utils/Logger.h"
#include "Core/Renderer/Texture.h"

const Renderer::Texture Renderer::createTexture(const char* path, const TextureFormat& format) {
  Texture texture;
  
  // load image data
  int32_t width, height, nrChannels;
  uint8_t *data = stbi_load(path, &width, &height, &nrChannels, 0);
  
  if (!data) {
    LOGGER_ERROR("TEXURE::FAILED_TO_LOAD_TEXTURE");
  } else {
    // generate Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE2, texture);

    // configure texture
    glTexParameteri(GL_TEXTURE2, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE2, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE2, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE2, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    uint32_t gl_format;
    if (format == TextureFormat::RGBA) gl_format = GL_RGBA;
    else if (format == TextureFormat::RGB) gl_format = GL_RGB;
    glTexImage2D(GL_TEXTURE2, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE2);
  }

  stbi_image_free(data);

  return texture;
}
