#include "gfx/buffer.h"
#include "gfx/shader.h"
#include "gfx/window.h"
#include <GLFW/glfw3.h>

int main() {
  windowCreate("engine C API", 800, 800);

  GLuint solid_shader = shaderCreate("assets/shaders/solid_vs.glsl",
                                     "assets/shaders/solid_fs.glsl");
  float vertices[] = {
      -1.0f, 1.0f,  // 0
      1.0f,  1.0f,  // 1
      -1.0f, -1.0f, // 2
      1.0f,  -1.0f, // 3
  };
  unsigned int index[] = {0, 1, 2, 2, 1, 3};

  Buffer vertexBuffer = bufferCreate(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  bufferData(&vertexBuffer, sizeof(vertices), vertices);
  Buffer indexBuffer = bufferCreate(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  bufferData(&indexBuffer, sizeof(index), index);
  glad_glEnableVertexAttribArray(0);
  glad_glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  int u_time = shaderUniformLoc(solid_shader, "u_time");
  int u_resolution = shaderUniformLoc(solid_shader, "u_resolution");
  int u_mouse = shaderUniformLoc(solid_shader, "u_mouse");

  while (!windowExit()) {
    shaderUniformf(1, u_time, glfwGetTime());
    shaderUniformf(2, u_resolution, 800, 800);
    shaderUniformf(2, u_mouse, 800, 800);

    glad_glDrawElements(GL_TRIANGLES, sizeof(index) / sizeof(int),
                        GL_UNSIGNED_INT, 0);
    windowUpdate();
  }

  bufferDestroy(&vertexBuffer);
  shaderDestroy(solid_shader);
  windowDestroy();
  return 0;
}
