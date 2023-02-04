//
// Created by richard may clarkson on 19/12/2022.
//
#include "iomanip"
#include "engine/imodel.h"
#include "engine/camera.h"
#include "engine/fbo.h"
#include "engine/mesh.h"
#include "stb_image.h"
#include "ember.h"
#include "glad.h"

namespace GL {
  bool depthEnabled{false};
  bool blendEnabled{false};
  bool cullEnabled{false};

  bool depthSaved{false};
  bool blendSaved{false};
  bool cullSaved{false};

  bool rendering3d = false;

  std::array<glm::mat4, 7> stack;
  glm::mat4* model;
  int stackIdx{0};

  glm::mat4 proj;
  glm::mat4 look;
  glm::mat4 lightSpace;
  Framebuffer* fbo;
  Framebuffer* postProcessFbo;
  Framebuffer* intermediaryFbo;
  Camera cam(glm::vec3(0.f), glm::vec3(0., 1., 0.));
  Shader shader;

  void init() {
    for (int i = 0; i < 7; i++) {
      stack[i] = glm::mat4(1.0f);
    }
    model = &stack[0];
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      die("Failed to initialize GLAD!");
    }
  }

  void save_state() {
    depthSaved = depthEnabled;
    blendSaved = blendEnabled;
    cullSaved = cullEnabled;
  }

  void restore_state() {
    depth(depthSaved);
    blend(blendSaved);
    cull(cullSaved);
  }

  void depth(bool on) {
    if (depthEnabled == on) return;
    depthEnabled = on;
    if (on) {
      glEnable(GL_DEPTH_TEST);
    } else {
      glDisable(GL_DEPTH_TEST);
    }
  }

  void blend(bool on) {
    if (blendEnabled == on) return;
    blendEnabled = on;
    if (on) {
      glEnable(GL_BLEND);
    } else {
      glDisable(GL_BLEND);
    }
  }

  void cull(bool on) {
    if (cullEnabled == on) return;
    cullEnabled = on;
    if (on) {
      glEnable(GL_CULL_FACE);
    } else {
      glDisable(GL_CULL_FACE);
    }
  }

  void as_3d() {
    float aspect = (float) width / (float) height;
    proj = glm::perspective(glm::radians(45.f), aspect, 0.1f, 100.f);
    rendering3d = true;
  }

  void as_2d() {
    proj = glm::ortho(0.f, (float) width, (float) height, 0.f, -2.f, 2.f);
    rendering3d = false;
  }

  void set_defaults() {
    shader.set_float("u_time", (float) glfwGetTime(), true);
    shader.set_mat4("u_proj", proj, true);
    shader.set_mat4("u_look", look, true);
    shader.set_mat4("u_model", *model, true);
    shader.set_mat4("u_lightSpace", lightSpace, true);
    shader.set_vec3("u_camPos", cam.view_pos(), true);
    shader.set_vec2("u_screenSize", glm::vec2(Ember::width, Ember::height), true);
    shader.set_vec2("u_aaRad", {0, 0}, true);
    shader.set_vec3("u_playerPos", cam.pos, true);
  }
}