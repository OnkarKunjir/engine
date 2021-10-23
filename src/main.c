#include "gfx/buffer.h"
#include "gfx/shader.h"
#include "gfx/window.h"

int main() {
  windowCreate("engine C API", 800, 800);

  GLuint solid_shader = shaderCreate("assets/shaders/solid_vs.glsl",
                                     "assets/shaders/solid_fs.glsl");
  float vertices[] = {
      -0.5f, 0.5f,  // 0
      0.5f,  0.5f,  // 1
      -0.5f, -0.5f, // 2
      0.5f,  -0.5f, // 3
  };
  unsigned int index[] = {0, 1, 2, 2, 1, 3};

  Buffer vertexBuffer = bufferCreate(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  bufferData(&vertexBuffer, sizeof(vertices), vertices);

  Buffer indexBuffer = bufferCreate(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  bufferData(&indexBuffer, sizeof(index), index);

  glad_glEnableVertexAttribArray(0);
  glad_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  while (!windowExit()) {
    glad_glDrawElements(GL_TRIANGLES, sizeof(index) / sizeof(int),
                        GL_UNSIGNED_INT, 0);
    windowUpdate();
  }

  bufferDestroy(&vertexBuffer);
  shaderDestroy(solid_shader);
  windowDestroy();
  return 0;
}
