//
// Created by richard may clarkson on 05/01/2023.
//
#include "engine/lightmap.h"

namespace Ember {
  void Lightmap::draw() const {
    die_if_gl("Lightmap::draw>begin");
    fbo.use();
    fbo.clear();
    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_DEPTH_BUFFER_BIT);
    GL::lightSpace = glm::ortho(-10.f, 10.f, -10.f, 10.f, 1.f, 500.f) * lookAt(lightDir * 10.f, glm::vec3(0.f), glm::vec3(0, 1, 0));
    Ember::draw_3d();
    Framebuffer::unuse();
    die_if_gl("Lightmap::draw>end");
  }
}