//
// Created by richard may clarkson on 21/12/2022.
//

#ifndef GLENGINE_MODEL_H
#define GLENGINE_MODEL_H

#include <algorithm>
#include "global.h"
#include "mesh.h"
#include "tex.h"

namespace Ember {
  static std::unordered_map<std::string, void*> __model_cache;

  struct Model {
    struct Face {
      uint p0, p1, p2, n0, n1, n2;
      glm::vec3 color;
      glm::vec3 shadingModel;
    };

    struct Vertex {
      glm::vec3 pos;
      glm::vec3 normal;
      glm::vec3 color;
      glm::vec3 shadingModel;
    };

    enum ArgType {
      COLOR,
      SHADING_MODEL,
      WINDINESS
    };

    using Arg = std::unordered_map<std::string, glm::vec4>;
    using Args = std::unordered_map<ArgType, Arg>;

    Mesh<Vertex>* mesh;
    Shader shader;
    std::vector<Face> faces;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;

    Model(const std::string& src, Args args);

    void to_mesh() const;

    static Shader get_shader() {
      static Shader shader;
      if (!shader.handle) {
        shader = Shader("res/shader/model.vert", "res/shader/imodel.frag");
      }
      return shader;
    }

    static std::string combine(const std::string& src, const Model::Args& args) {
      std::stringstream out;
      out << src;
      for (auto& it : args)
        for (auto& [key, value] : it.second)
          out << key << value.x << value.y << value.z << value.w;

      return out.str();
    }

    static Model* get(const std::string& src, const Model::Args& colors) {
      std::string key = combine(src, colors);
      if (__model_cache.find(key) == __model_cache.end()) {
        __model_cache[key] = new Model(src, colors);
      }
      return (Model*)__model_cache[key];
    }

    inline void scale(float s) {
      for (glm::vec3& pos : positions) {
        pos *= s;
      }
      to_mesh();
    }

    inline void scale(glm::vec3 s) {
      for (glm::vec3& pos : positions) {
        pos *= s;
      }
      to_mesh();
    }

    inline void rotate(float angle, glm::vec3 axis) {
      for (glm::vec3& pos : positions) {
        pos = glm::rotate(glm::mat4(1.f), angle, axis) * glm::vec4(pos, 1.f);
      }
      for (glm::vec3& normal : normals) {
        normal = glm::rotate(glm::mat4(1.f), angle, axis) * glm::vec4(normal, 1.f);
      }
      to_mesh();
    }

    inline void translate(glm::vec3 t) {
      for (glm::vec3& pos : positions) {
        pos += t;
      }
      to_mesh();
    }

    void draw(const glm::vec3& pos) const {
      GL::push();
      GL::translate(pos);
      mesh->draw();
      GL::pop();
    }
  };
}

#endif //GLENGINE_MODEL_H
