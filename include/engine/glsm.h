//
// Created by richard may clarkson on 19/12/2022.
//

#ifndef GLENGINE_GLSM_H
#define GLENGINE_GLSM_H

#include "camera.h"
#include "fbo.h"
#include "global.h"
#include "shader.h"

using namespace Ember;

namespace GL {
  extern bool depthEnabled;
  extern bool blendEnabled;
  extern bool cullEnabled;

  extern bool depthSaved;
  extern bool blendSaved;
  extern bool cullSaved;

  extern bool rendering3d;

  extern std::array<glm::mat4, 7> stack;
  extern glm::mat4* model;
  extern int stackIdx;

  extern glm::mat4 proj;
  extern glm::mat4 look;
  extern glm::mat4 lightSpace;
  extern Framebuffer* fbo;
  extern Framebuffer* postProcessFbo;
  extern Framebuffer* intermediaryFbo;
  extern Camera cam;
  extern Shader shader;

  void init();

  inline void push() {
    stackIdx++;
    stack[stackIdx] = glm::mat4(stack[stackIdx - 1]);
    model = &stack[stackIdx];
  }

  inline void pop() {
    stackIdx--;
    model = &stack[stackIdx];
  }

  inline void translate(const glm::vec3& vec) {
    stack[stackIdx] = translate(*model, vec);
    model = &stack[stackIdx];
  }

  inline void rotate(float deg, const glm::vec3& vec) {
    stack[stackIdx] = rotate(*model, glm::radians(deg), vec);
    model = &stack[stackIdx];
  }

  inline void scale(const glm::vec3& vec) {
    stack[stackIdx] = scale(*model, vec);
    model = &stack[stackIdx];
  }

  inline void identity() {
    stack[stackIdx] = glm::identity<glm::mat4>();
    model = &stack[stackIdx];
  }

  static Shader get_dither() {
    static Shader dither;
    if (!dither.handle) {
      dither = Shader("res/shader/dither.vert", "res/shader/dither.frag");
      dither.array("palette", 256);
    }
    return dither;
  }

  void set_defaults();

  void save_state();

  void restore_state();

  void depth(bool on);

  void blend(bool on);

  void cull(bool on);

  void as_2d();
  void as_3d();
}

#endif //GLENGINE_GLSM_H
