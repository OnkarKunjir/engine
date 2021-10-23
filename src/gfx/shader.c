#include "shader.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *shaderRead(const char *path);
GLuint shaderCompile(GLenum shader_type, char *restrict path,
                     char *restrict src);
char *shaderRead(const char *path) {
  FILE *shader_file;

  if ((shader_file = fopen(path, "r")) == NULL) {
    return NULL;
  }
  fseek(shader_file, 0, SEEK_END);
  // get the file size.
  int size = ftell(shader_file);
  rewind(shader_file);

  char *shader_src = (char *)calloc(size + 1, sizeof(char));
  fread(shader_src, sizeof(char), size, shader_file);
  fclose(shader_file);

  return shader_src;
}

GLuint shaderCompile(GLenum shader_type, char *restrict path,
                     char *restrict src) {
  GLuint shader = glad_glCreateShader(shader_type);

  glad_glShaderSource(shader, 1, (const GLchar *const *)&src, NULL);
  glad_glCompileShader(shader);

  GLint status;
  glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &status);
    char gl_log[status + 1];
    glad_glGetShaderInfoLog(shader, status, NULL, gl_log);
    printf("Failed to compile shader %s:\n%s\n", path, gl_log);
    return 0;
  }
  return shader;
}

GLuint shaderCreate(char *restrict vs_path, char *restrict fs_path) {

  char *vs_src = shaderRead(vs_path);
  if (vs_src == NULL) {
    printf("Failed to read %s : %s\n", vs_path, strerror(errno));
    return 0;
  }

  GLuint vs = shaderCompile(GL_VERTEX_SHADER, vs_path, vs_src);
  free(vs_src);
  if (!vs) {
    return 0;
  }

  char *fs_src = shaderRead(fs_path);
  if (fs_src == NULL) {
    printf("Failed to read %s : %s\n", fs_path, strerror(errno));
    return 0;
  }
  GLuint fs = shaderCompile(GL_FRAGMENT_SHADER, fs_path, fs_src);
  free(fs_src);
  if (!fs) {
    return 0;
  }

  GLuint program = glad_glCreateProgram();
  glad_glAttachShader(program, vs);
  glad_glAttachShader(program, fs);
  glad_glLinkProgram(program);

  glad_glDeleteShader(vs);
  glad_glDeleteShader(fs);

  glad_glUseProgram(program);

  return program;
}

void shaderUse(GLuint program) { glad_glUseProgram(program); }

void shaderDestroy(GLuint program) { glad_glDeleteProgram(program); }
