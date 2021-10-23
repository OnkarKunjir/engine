#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

/**
 * @return shader program by compiling and linking vertex and fragment shader.
 * If case of error returns 0.
 */
GLuint shaderCreate(char *restrict vs_path, char *restrict fs_path);

void shaderUse(GLuint program);

void shaderDestroy(GLuint program);

#endif /* SHADER_H */
