//
// Created by richard may clarkson on 05/01/2023.
//

#ifndef LILY_IML_LINES_H
#define LILY_IML_LINES_H

#include "shader.h"
#include "mesh.h"

namespace Ember::Lines {
  static Shader get_shader() {
    static Shader sh;
    if (!sh.handle) {
      sh = Shader("res/shader/Lines.vert", "res/shader/Lines.frag", "res/shader/Lines.geom");
    }
    return sh;
  }

  struct LineVertex {
    glm::vec3 pos;
    float width;
    glm::vec4 color;
  };

  static Mesh<LineVertex>* get_mesh() {
    static Mesh<LineVertex>* mesh = nullptr;
    if (!mesh) {
      mesh = new Mesh<LineVertex>(DrawModes::line, {Attribute::FLOAT4, Attribute::FLOAT4});
    }
    return mesh;
  }

  static void add(const glm::vec3& a, const glm::vec3& b, float width, const glm::vec4& color) {
    get_mesh()->line(
      get_mesh()->put({a, width, color}),
      get_mesh()->put({b, width, color})
    );
  }

  static void draw(const glm::vec3& a, const glm::vec3& b, float width, const glm::vec4& color) {
    get_mesh()->begin();
    get_mesh()->line(
      get_mesh()->put({a, width, color}),
      get_mesh()->put({b, width, color})
    );
    get_mesh()->draw();
  }

}

#endif //LILY_IML_LINES_H
