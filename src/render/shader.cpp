#define __FILENAME__ "shader.cpp"

#include "render/shader.hpp"
#include "utils/log.hpp"

#include <fstream>
#include <glad/gl.h>
#include <sstream>
#include <string>

Shader::Shader(const std::string &vs_path, const std::string &fs_path,
               const std::string &out) {

  // compile both the shaders.

  unsigned int vs = compile_shader(read_shader_src(vs_path), GL_VERTEX_SHADER);
  unsigned int fs =
      compile_shader(read_shader_src(fs_path), GL_FRAGMENT_SHADER);

  // create shader program
  _id = glad_glCreateProgram();
  glad_glAttachShader(_id, vs);
  glad_glAttachShader(_id, fs);
  glad_glBindFragDataLocation(_id, 0, out.c_str());
  glad_glLinkProgram(_id);

  bind();

  // delete shaders
  glad_glDeleteShader(vs);
  glad_glDeleteShader(fs);
}

Shader::~Shader() { glad_glDeleteProgram(_id); }

// public function
void Shader::bind() const { glad_glUseProgram(_id); }

int Shader::get_uniform(const std::string &name) const {
  return glad_glGetUniformLocation(_id, name.c_str());
}

void Shader::set_uniform_matrix4fv(const std::string &name, const float *matrix,
                                   bool transpose) const {
  glad_glUniformMatrix4fv(get_uniform(name), 1, transpose, matrix);
}

void Shader::set_uniform_float3fv(const std::string &name,
                                  const float *arr) const {
  glad_glUniform3fv(get_uniform(name), 1, arr);
}

// private functions
std::string Shader::read_shader_src(const std::string &path) const {

  std::stringstream ss;

  std::fstream src;
  src.open(path.c_str(), std::ios::in);
  if (!src.is_open()) {
    Log::error(__FILENAME__, "Failed to open file : " + path);
  }
  std::string line;
  while (std::getline(src, line)) {
    ss << line << "\n";
  }
  src.close();

  return ss.str();
}

unsigned int Shader::compile_shader(const std::string &src,
                                    unsigned int shader_type) const {

  // shader type in string format.
  std::string shader_type_str =
      (shader_type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader");

  unsigned int shader = glad_glCreateShader(shader_type);
  if (!shader) {
    Log::error(__FILENAME__, "Failed to create shader " + shader_type_str);
  }

  // compiling shader
  const char *csrc = src.c_str();
  glad_glShaderSource(shader, 1, &csrc, nullptr);
  glad_glCompileShader(shader);

  // checking if compilation was successful or not
  int compile_status = 0;
  glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

  if (!compile_status) {

    int log_len = 0;
    glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

    std::string log(log_len, 0);
    glad_glGetShaderInfoLog(shader, log_len, nullptr, (char *)log.c_str());

    Log::error(__FILENAME__, "Failed to compile " + shader_type_str, false);
    Log::error(__FILENAME__, log);
  }

  return shader;
}
