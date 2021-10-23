#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"

GLFWwindow *window = NULL;

/**
 * Error callback function for glfw.
 */
void error_callback(int error_code, const char *description) {
  printf("[%d] : %s\n", error_code, description);
}

// TODO: add options to change the properties for the winodw.
void windowCreate(const char *title, int width, int height) {

  // allows creation of only one window at a time.
  if (window != NULL) {
    printf("Creation of multiple windows is not supported.\n");
    return;
  }

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    printf("Failed to initalize glfw");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  if (!(window = glfwCreateWindow(width, height, title, NULL, NULL))) {
    glfwTerminate();
    printf("Failed to create window");
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  // vsync turned off by default.
  glfwSwapInterval(0);

  if (!gladLoadGL(glfwGetProcAddress)) {
    windowDestroy(window);
    printf("Failed to load openGL");
    exit(EXIT_FAILURE);
  }
  glad_glClear(GL_COLOR_BUFFER_BIT);
}

void windowFill() {}

void windowUpdate() {
  glfwSwapBuffers(window);
  glfwPollEvents();
  glad_glClear(GL_COLOR_BUFFER_BIT);
}

int windowExit() { return glfwWindowShouldClose(window); }

void windowDestroy() {
  glfwDestroyWindow(window);
  glfwTerminate();

  // reset value of window pointer if user decides to create new window again
  // for some reason.
  window = NULL;
}
