#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int num_segments = 50;

void drawCircle(float cx, float cy, float r, float colorR, float colorG,
                float colorB) {
  glLineWidth(1); // Establecer el grosor de la línea
  glBegin(GL_POLYGON);
  glColor3f(colorR, colorG, colorB); // Color interior del círculo
  for (int i = 0; i < num_segments; i++) {
    float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
    float x = r * cosf(theta);
    float y = r * sinf(theta);
    glVertex2f(x + cx, y + cy);
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1.0f, 1.0f, 1.0f); // Color del borde del círculo (blanco)
  for (int i = 0; i < num_segments; i++) {
    float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
    float x = r * cosf(theta);
    float y = r * sinf(theta);
    glVertex2f(x + cx, y + cy);
  }
  glEnd();
}

void drawLine(float x1, float y1, float x2, float y2) {
  glLineWidth(5); // Establecer el grosor de la línea
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
}

int main() {
  GLFWwindow *window;

  if (!glfwInit()) {
    std::cerr << "Error initializing GLFW\n";
    return -1;
  }

  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Circles and Lines Example",
                            NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw circles
    drawCircle(-0.5f, 0.5f, 0.2f, 1.0f, 0.0f, 0.0f);  // Círculo rojo
    drawCircle(0.5f, 0.5f, 0.2f, 0.0f, 1.0f, 0.0f);   // Círculo verde
    drawCircle(-0.5f, -0.5f, 0.2f, 0.0f, 0.0f, 1.0f); // Círculo azul
    drawCircle(0.5f, -0.5f, 0.2f, 1.0f, 0.0f, 0.0f);  // Círculo amarillo

    // Draw lines between circles
    glColor3f(0.5f, 0.5f, 0.5f); // Color de las líneas (gris)
    // Línea del primer círculo al segundo círculo
    // glBegin(GL_LINES);
    drawLine(-0.3, 0.3 + 0.2f, 0.3, 0.3 + 0.2f);
    // Línea del primer círculo al tercer círculo
    drawLine(-0.3f - 0.2f, 0.3f, -0.3f - 0.2f, -0.3f);
    // Línea del segundo círculo al cuarto círculo
    drawLine(0.3f + 0.2f, 0.3f, 0.3f + 0.2f, -0.3f);
    drawLine(-0.3f, -0.3f - 0.2f, 0.3f, -0.3f - 0.2f);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
