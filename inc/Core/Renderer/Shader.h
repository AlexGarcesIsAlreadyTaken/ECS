#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include "glad/glad.h"
#include "Utils/Constants.h"
#include <type_traits>

// Represents an object that deals with renderization:
// - Shaders
namespace Renderer {
  typedef uint32_t Shader;

  // Since variables like Shader are too redundant to
  // use OOP (if we call to setShader using classes we were still
  // modifying which shader is being used in the "global" scene)
  // However, we also need to know which shader is currently being used
  // So using an anonymous namespace brings us a solution that fits for now.
  namespace {
    static Shader currentShader;
  };

  const Shader createShader(const char *vertexPath, const char *fragmentPath);

  inline void useShader(Shader shader) { currentShader = shader; glUseProgram(shader); }

  template <typename T>
  inline void setUniform(const char *name, const T& value) {
    int32_t loc = glGetUniformLocation(currentShader, name);
    if (std::is_same_v<T, Boolean>) glUniform1ui(loc, uint32_t(value));
    else if (std::is_same_v<T, uint32_t>) glUniform1ui(loc, value);
    else if (std::is_same_v<T, int32_t>) glUniform1i(loc, value);
  }
};

#endif
