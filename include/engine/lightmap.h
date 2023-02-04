//
// Created by richard may clarkson on 05/01/2023.
//

#ifndef GLENGINE_LIGHTMAP_H
#define GLENGINE_LIGHTMAP_H

#include "camera.h"
#include "fbo.h"
#include "ember.h"
#include "shader.h"
#include "glsm.h"

namespace Ember {
  struct Lightmap {
    Framebuffer fbo;
    glm::vec3 lightDir{};

    static Shader get_shader() {
      static Shader shader;
      if (!shader.handle) {
        shader = Shader("res/shader/ilightmap.vert", "res/shader/lightmap.frag");
      }
      return shader;
    }

    Lightmap() = default;

    explicit Lightmap(const glm::vec3& lightDir) : lightDir(lightDir) {
      fbo = Framebuffer(1024, 1024, false, true, false);
    }

    void draw() const;
  };
}

#endif //GLENGINE_LIGHTMAP_H
