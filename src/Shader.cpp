#include "glad/glad.h"
#include "Core/Renderer/Shader.h"
#include "Utils/Constants.h"
#include "Utils/Logger.h"
#include <fstream>
#include <sstream>

const Renderer::Shader Renderer::createShader(const char *vertexPath, const char *fragmentPath) {
  std::string vertexCode, fragmentCode;
  std::ifstream vShaderFile, fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    // Open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    // Read Files
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // Close files
    vShaderFile.close();
    fShaderFile.close();

    // Convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch(std::ifstream::failure e) {
    LOGGER_ERROR("SHADER::FILE_NOT_SUCCESFULLY_READ");
  }

  const char *vShaderSource = vertexCode.c_str();
  const char *fShaderSource = fragmentCode.c_str();

  Shader vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderSource, nullptr);
  glCompileShader(vertexShader);

  char info[512];
  int32_t success;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(info), nullptr, info);
    LOGGER_ERROR("SHADER::VERTEX::COMPILATION_FAILED::" << info);
  }

  Shader fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderSource, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(info), nullptr, info);
    LOGGER_ERROR("SHADER::VERTEX::COMPILATION_FAILED::" << info);
  }

  Shader shader = glCreateProgram();
  glAttachShader(shader, vertexShader);
  glAttachShader(shader, fragmentShader);
  glLinkProgram(shader);

  glGetShaderiv(shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, sizeof(info), nullptr, info);
    LOGGER_ERROR("SHADER::PROGRAM::LINKING_FAILED::" << info);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shader;
}
