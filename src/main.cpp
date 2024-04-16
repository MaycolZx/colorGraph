
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

void drawCircle(float cx, float cy, float r, int num_segments) {
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < num_segments; i++) {
    float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
    float x = r * cosf(theta);
    float y = r * sinf(theta);
    glVertex2f(x + cx, y + cy);
  }
  glEnd();
}

int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cerr << "Error initializing GLFW\n";
    return -1;
  }

  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Circle Example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw circle
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    drawCircle(0.0f, 0.0f, 0.5f, 50);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
