#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#define shaderUse(program) glad_glUseProgram(program)
#define shaderDestroy(program) glad_glDeleteProgram(program)

#define shaderUniformLoc(program, uniform)                                     \
  glad_glGetUniformLocation(program, uniform)

#define shaderUniformf(n, location, ...)                                       \
  glad_glUniform##n##f(location, __VA_ARGS__)

/**
 * @return shader program by compiling and linking vertex and fragment shader.
 * If case of error returns 0.
 */
GLuint shaderCreate(char *restrict vs_path, char *restrict fs_path);

#endif /* SHADER_H */
