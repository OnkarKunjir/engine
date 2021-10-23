#ifndef WINDOW_H
#define WINDOW_H

/**
 * Function creates glfw window and initalizes openGL context.
 * NOTE: Call this function before calling any openGL functions.
 */
void windowCreate(const char *title, int width, int height);

/**
 * Swaps window buffer and polls events.
 */
void windowUpdate();

void windowFill();

/**
 * @return 1 if exit event was tirggerd else 0.
 */
int windowExit();

/**
 * Destroyes created window and deallocates glfw resources
 */
void windowDestroy();

#endif /* WINDOW_H */
