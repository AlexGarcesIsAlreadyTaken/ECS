#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include "glad/glad.h"
#include "Utils/Constants.h"
#include "Core/Math/Vec3.h"
#include <type_traits>
#include "Utils/Logger.h"

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

  inline void useShader(Shader shader) { currentShader = shader; glUseProgram(currentShader); }

  template <typename T> requires (std::is_same_v<T, Math::vec3>)
  inline void setUniform(const char *name, const T& value) {
    int32_t loc = glGetUniformLocation(currentShader, name);
    glUniform3f(loc, value.x, value.y, value.z);
  }

  template <typename T> requires (std::is_same_v<T, Math::ivec3>)
  inline void setUniform(const char *name, const T& value) {
    int32_t loc = glGetUniformLocation(currentShader, name);
    glUniform3i(loc, value.x, value.y, value.z);
  }
};

#endif
