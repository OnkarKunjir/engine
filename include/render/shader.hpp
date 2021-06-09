#pragma once

#include <string>

class Shader {

private:
  int _id;

public:
  /**
   *Shader constructor
   *@param vs_path vertex shader path
   *@param fs_path fragment shader path
   *@param out fragment shader outptu variable
   */
  Shader(const std::string &vs_path, const std::string &fs_path,
         const std::string &out);
  ~Shader();

  /// binds shader program
  void bind() const;

  /**
   *Returns uniform location from shader.
   *@param name name of uniform defined in shader srouce code.
   */
  int get_uniform(const std::string &name) const;

private:
  /**
   *compiles shader program
   *@param src source code of shader program
   *@param type of shader program (eg. GL_FRAGMENT_SHADER, GL_VERTEX_SHADER, ..)
   */
  unsigned int compile_shader(const std::string &src,
                              unsigned int shader_type) const;
  /**
   *reads shader source code and return as a string
   *@param path relative/absolute path to shader
   *@return contents of shader `path`
   */
  std::string read_shader_src(const std::string &path) const;
};
