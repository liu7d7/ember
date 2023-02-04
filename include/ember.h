//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_PIQU_H
#define GLENGINE_PIQU_H

#include "global.h"
#include "engine/fbo.h"
#include "engine/camera.h"
#include "engine/shader.h"
#include "engine/stb_font.h"

namespace Ember {
  extern GLFWwindow* window;

  extern uint mouseState;
  extern float mouseX, mouseY, lastMouseX, lastMouseY;
  extern float tickDelta;
  extern bool firstMove;
  extern int width, height;
  extern int age;
  static const glm::vec4 yellow = 0xfff9db7b_vec4;
  static const glm::vec4 pink = 0xfffb97ae_vec4;

  void init();

  void run();

  void tick();

  void draw_3d();

  void draw(double dt);
}

#endif //GLENGINE_PIQU_H
