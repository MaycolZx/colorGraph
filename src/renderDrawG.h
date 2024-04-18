// #include "../include/glut-3.6/include/GL/glut.h"
#include "coloreo.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

const float radiusG = 0.1f;

const int WIDTH = 800;
const int HEIGHT = 600;
const int num_segments = 50;

const float TEXT_SIZE = 50.0f;

vector<CNode *> nodosGraphC;
float colorRGB[3][3] = {
    {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  float heightF = 0.1f, widthF = 0.5f;
  float positionInit[2] = {-0.95, -0.90};
  float valorCapX, valorCapY;
  if (positionInit[0] < 0) {
    valorCapX = WIDTH + positionInit[0] * WIDTH;
  } else {
    valorCapX = positionInit[0] * WIDTH;
  }
  if (positionInit[1] < 0) {
    valorCapY = (-1) * positionInit[1] * HEIGHT;
  } else {
    valorCapY = HEIGHT + positionInit[1] * HEIGHT;
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (xpos >= valorCapX && xpos <= valorCapX + ((widthF * WIDTH) / 2) &&
        ypos >= valorCapY && ypos <= valorCapY + ((heightF * HEIGHT) / 2)) {
      std::cout << "Soy un botón" << std::endl;
      for (size_t i = 0; i < nodosGraphC.size(); i++) {
        cout << "valor: " << nodosGraphC[i]->name << ' '
             << nodosGraphC[i]->color << '\n';
      }
    }
  }
}

void drawRectangle() {
  float heightF = 0.1f, widthF = 0.5f;
  float positionInit[2] = {-0.90, -0.80};
  glBegin(GL_QUADS);
  glColor3f(0.5f, 0.5f, 0.5f); // Color gris
  // glVertex2f(0, 0);
  // glVertex2f(RECT_WIDTH / 100, 0);
  // glVertex2f(RECT_WIDTH / 100, RECT_HEIGHT / 100);
  // glVertex2f(0, RECT_HEIGHT / 100);
  glVertex2f(positionInit[0], positionInit[1]);
  glVertex2f(positionInit[0], positionInit[1] - heightF);
  glVertex2f(positionInit[0] + widthF, positionInit[1] - heightF);
  glVertex2f(positionInit[0] + widthF, positionInit[1]);
  glEnd();
}

void drawCircle(float cx, float cy, float r, int colorParam) {
  glLineWidth(1); // Establecer el grosor de la línea
  glBegin(GL_POLYGON);
  glColor3f(colorRGB[colorParam - 1][0], colorRGB[colorParam - 1][1],
            colorRGB[colorParam - 1][2]); // Color interior del círculo
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

void graphoCaseOne(float adjust, int valorResRec) {
  if (valorResRec == 0) {

    // Draw circles
    drawCircle(-0.5f - adjust, 0.5f, radiusG,
               nodosGraphC[0]->color); // Círculo rojo-A
    drawCircle(0.5f - adjust * 2, 0.5f, radiusG,
               nodosGraphC[2]->color); // Círculo verde-D
    // drawCircle(0.5f - adjust * 2, 0.5f, radiusG, nodosGraphC[2]->color);
    drawCircle(-0.5f - adjust, -0.5f, radiusG,
               nodosGraphC[1]->color); // Círculo azul-B
    drawCircle(0.5f - adjust * 2, -0.5f, radiusG,
               nodosGraphC[4]->color); // Circulo-C
    // drawCircle(0.5f - adjust * 2, 0.5f, radiusG, nodosGraphC[2]->color);

    drawCircle(0.5f + adjust, -0.5f + 0.5f, radiusG,
               nodosGraphC[3]->color); // Circulo-E
  } else {
    // Draw circles
    drawCircle(-0.5f - adjust, 0.5f, radiusG,
               nodosGraphC[0]->color); // Círculo rojo-A
    drawCircle(0.5f - adjust * 2, 0.5f, radiusG,
               nodosGraphC[3]->color); // Círculo verde-D
    drawCircle(-0.5f - adjust, -0.5f, radiusG,
               nodosGraphC[1]->color); // Círculo azul-B
    drawCircle(0.5f - adjust * 2, -0.5f, radiusG,
               nodosGraphC[2]->color); // Circulo-C
    drawCircle(0.5f + adjust, -0.5f + 0.5f, radiusG,
               nodosGraphC[4]->color); // Circulo-E
  }

  // Draw lines between circles
  glColor3f(0.5f, 0.5f, 0.5f); // Color de las líneas (gris)
  // Línea del primer círculo al segundo círculo
  // glBegin(GL_LINES);
  drawLine(-0.3 - radiusG - adjust, 0.3 + 2 * radiusG, 0.3 - radiusG - adjust,
           0.3 + 2 * radiusG);
  // Línea del primer círculo al tercer círculo
  drawLine(-0.3f - 2 * radiusG - adjust, 0.3f + radiusG,
           -0.3f - 2 * radiusG - adjust, -0.3f - radiusG);
  // Línea del segundo círculo al cuarto círculo
  drawLine(0.3f - 2 * radiusG, 0.3f + radiusG, 0.3f - 2 * radiusG,
           -0.3f - radiusG);
  drawLine(-0.3f - radiusG - adjust, -0.3f - 2 * radiusG,
           0.3f - radiusG - adjust, -0.3f - 2 * radiusG);
  ///
  drawLine(0.3f - 2 * radiusG, 0.3f + radiusG, 0.3f + radiusG + adjust,
           -0.3f + radiusG + adjust);
  drawLine(0.3f - 2 * radiusG, -0.3f - radiusG, 0.3f + radiusG + adjust,
           -0.3f + radiusG + adjust);
  //
  drawLine(-0.3f - 2 * radiusG - adjust, 0.3f + radiusG,
           0.3f + radiusG + adjust, -0.3f + radiusG + adjust);
}

void graphoCaseTwo(float adjust, int valorResRec) {
  //
  if (valorResRec == 0) {
    drawCircle(-0.5f - adjust, 0.5f, radiusG,
               nodosGraphC[6]->color); // Círculo rojo A
    drawCircle(0.5f - adjust * 2, 0.5f, radiusG,
               nodosGraphC[0]->color); // Círculo verde D
    // Falta la linea de D-F
    drawCircle(0.5f - radiusG, 0.5f, radiusG,
               nodosGraphC[4]->color); // Circulo-E-
    drawCircle(0.5f - radiusG, -0.5f, radiusG,
               nodosGraphC[1]->color); // Circulo-F
    //
    drawCircle(-0.5f - adjust, -0.5f, radiusG,
               nodosGraphC[2]->color); // Circulo-B-
    drawCircle(0.5f - adjust * 2, -0.5f, radiusG,
               nodosGraphC[3]->color); // Circulo-C
    //
    drawCircle(0.5f + adjust, -0.5f + 0.5f, radiusG,
               nodosGraphC[5]->color); // Circulo-G
  } else {
    drawCircle(-0.5f - adjust, 0.5f, radiusG,
               nodosGraphC[0]->color); // Círculo rojo A
    drawCircle(0.5f - adjust * 2, 0.5f, radiusG,
               nodosGraphC[3]->color); // Círculo verde D
    // Falta la linea de D-F
    drawCircle(0.5f - radiusG, 0.5f, radiusG,
               nodosGraphC[4]->color); // Circulo-E-
    drawCircle(0.5f - radiusG, -0.5f, radiusG,
               nodosGraphC[5]->color); // Circulo-F
    //
    drawCircle(-0.5f - adjust, -0.5f, radiusG,
               nodosGraphC[1]->color); // Circulo-B-
    drawCircle(0.5f - adjust * 2, -0.5f, radiusG,
               nodosGraphC[2]->color); // Circulo-C
    //
    drawCircle(0.5f + adjust, -0.5f + 0.5f, radiusG,
               nodosGraphC[6]->color); // Circulo-G
  }
  glColor3f(0.5f, 0.5f, 0.5f);
  // Línea del primer círculo al segundo círculo
  drawLine(-0.3 - radiusG - adjust, 0.3 + 2 * radiusG, -0.3 - radiusG,
           0.3 + 2 * radiusG);
  // Línea del primer círculo al tercer círculo
  drawLine(-0.3f - 2 * radiusG - adjust, 0.3f + radiusG,
           -0.3f - 2 * radiusG - adjust, -0.3f - radiusG);
  // Línea del segundo círculo al cuarto círculo
  drawLine(-0.3f, 0.3f + radiusG, -0.3f, -0.3f - radiusG);
  drawLine(-0.3f - radiusG - adjust, -0.3f - 2 * radiusG, -0.3f - radiusG,
           -0.3f - 2 * radiusG);

  drawLine(-0.3 + radiusG, 0.3 + 2 * radiusG, 0.3, 0.3 + 2 * radiusG);
  // drawLine(-0.3 + radiusG, 0.3 + 2 * radiusG, -0.3, 0.3 + 2 * radiusG);
  //
  drawLine(0.3f + radiusG, 0.3f + radiusG, 0.3f + radiusG, -0.3f - radiusG);
  drawLine(0.3f, -0.3f - 2 * radiusG, 0.3f - radiusG - adjust,
           -0.3f - 2 * radiusG);
  drawLine(0.3f, -0.3f - 2 * radiusG, 0.3f - radiusG - adjust,
           0.3f + 2 * radiusG);

  ///
  drawLine(0.3f + 2 * radiusG, 0.3f + 2 * radiusG, 0.3f + radiusG + adjust,
           -0.3f - radiusG + adjust);
  drawLine(0.3f + 2 * radiusG, -0.3f - 2 * radiusG, 0.3f + radiusG + adjust,
           -0.3f - radiusG + adjust);
  //
  drawLine(-0.3f - 2 * radiusG - adjust, -0.3f - radiusG,
           0.3f + radiusG + adjust, -0.3f + adjust - radiusG);
}

int renderGraphColor(int changeGraph, vector<CNode *> nodosC, int valorResRec) {
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
  nodosGraphC = nodosC;
  glfwMakeContextCurrent(window);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle();

    if (changeGraph == 1) {
      graphoCaseOne(0.2f, valorResRec);
    } else {
      graphoCaseTwo(0.4f, valorResRec);
    }
    // Draw text
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    // drawText(WIDTH / 2.0f - TEXT_SIZE / 4.0f, HEIGHT / 2.0f - TEXT_SIZE
    // / 2.0f, "A");

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
