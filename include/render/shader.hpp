#pragma once

#include <string>

class Shader {

private:
  int _id;

public:
  /**
   *  Shader constructor
   *  @param vs_path vertex shader path
   *  @param fs_path fragment shader path
   *  @param out fragment shader outptu variable
   */
  Shader(const std::string &vs_path, const std::string &fs_path,
         const std::string &out);

  ~Shader();

  /// binds shader program
  void bind() const;

  /**
   *  Returns uniform location from shader.
   *  @param name name of uniform defined in shader srouce code.
   */
  int get_uniform(const std::string &name) const;

  /**
   *  Set the value of uniform value to a 4*4 matrix of type float.
   *  @param name Specify the name of uniform.
   *  @param matrix Specify the matrix to be assigned to uniform.
   *  @param transpose Take transpose of matrix.
   **/
  void set_uniform_matrix4fv(const std::string &name, const float *matrix,
                             bool transpose = false) const;

  /**
   *  Set value of uniform to an float type array of size 3.
   *  @param name Specify name of uniform.
   *  @param arr float array of size 3.
   */
  void set_uniform_float3fv(const std::string &name, const float *arr) const;

private:
  /**
   *  Compiles shader program
   *  @param src source code of shader program
   *  @param type of shader program (eg. GL_FRAGMENT_SHADER, GL_VERTEX_SHADER,
   * ..)
   */
  unsigned int compile_shader(const std::string &src,
                              unsigned int shader_type) const;
  /**
   *  reads shader source code and return as a string
   *  @param path relative/absolute path to shader
   *  @return contents of shader `path`
   */
  std::string read_shader_src(const std::string &path) const;
};
