//
// Created by richard may clarkson on 19/12/2022.
//

#ifndef GLENGINE_MESH_H
#define GLENGINE_MESH_H

#include <utility>

#include "buf.h"
#include "vao.h"
#include "shader.h"
#include "draw_mode.h"
#include "glsm.h"

namespace Ember {
  template<typename T>
  struct Mesh {
    DrawMode drawMode{};
    Buffer<T> vbo;
    Buffer<uint> ibo;
    VertexArray vao;
    int vertex{};
    int index{};
    bool building{};

    Mesh() = default;

    Mesh(const DrawMode& mode, const std::vector<Attribute>& attribs) :
      vbo(Buffer<T>(GL_ARRAY_BUFFER, 1200)), ibo(Buffer<uint>(GL_ELEMENT_ARRAY_BUFFER, 1200)), drawMode(mode),
      building(false), vao(VertexArray()), index(0), vertex(0) {
      vbo.use();
      ibo.use();
      vao.init(attribs);
    }

    int put(const T& p0) {
      vbo.put(p0);
      return vertex++;
    }

    void single(uint p0) {
      ibo.put(p0);
      index++;
    }

    void line(uint p0, uint p1) {
      ibo.put(p0);
      ibo.put(p1);
      index += 2;
    }

    void tri(uint p0, uint p1, uint p2) {
      ibo.put(p0);
      ibo.put(p1);
      ibo.put(p2);
      index += 3;
    }

    void quad(uint p0, uint p1, uint p2, uint p3) {
      ibo.put(p0);
      ibo.put(p1);
      ibo.put(p2);
      ibo.put(p2);
      ibo.put(p3);
      ibo.put(p0);
      index += 6;
    }

    void begin() {
      if (building) {
        die("Already building!");
      }
      building = true;

      vbo.clear();
      ibo.clear();

      vertex = index = 0;
    }

    void end() {
      if (!building) {
        die("Not building!");
      }
      building = false;

      if (index > 0) {
        vbo.upload();
        ibo.upload();
      }
    }

    void draw() {
      if (building) end();
      if (index == 0) return;

      GL::save_state();
      GL::blend(true);
      GL::depth(true);
      if (GL::rendering3d)
        GL::cull(true);
      GL::shader.use();
      GL::set_defaults();
      vao.use();
      ibo.use();
      vbo.use();
      glDrawElements(drawMode.cap, index, GL_UNSIGNED_INT, nullptr);
      GL::restore_state();
      die_if_gl("Mesh::draw>end");
    }

    void idraw(uint num) {
      if (building) end();
      if (index == 0 || num == 0) return;

      GL::save_state();
      GL::blend(true);
      GL::depth(true);
      if (GL::rendering3d)
        GL::cull(true);
      GL::shader.use();
      GL::set_defaults();
      vao.use();
      ibo.use();
      vbo.use();
      glDrawElementsInstanced(drawMode.cap, index, GL_UNSIGNED_INT, nullptr, (int) num);
      GL::restore_state();
    }
  };
}

#endif //GLENGINE_MESH_H
