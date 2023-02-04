//
// Created by richard may clarkson on 22/12/2022.
//
#include <iomanip>
#include <utility>
#include "engine/imodel.h"
#include "gtc/matrix_transform.hpp"

namespace Ember {
  InstancedModel::InstancedModel(const std::string& src, Model::Args args) : mod(new Model(src, std::move(args))) {
  }

  void InstancedModel::add(const glm::vec3& pos, const glm::mat4& other) {
    GL::push();
    GL::translate(pos);
    *GL::model = *GL::model * other;
    instances.push_back(*GL::model);
    GL::pop();
  }

  void InstancedModel::clear() {
    instances.clear();
  }

  void InstancedModel::draw(bool clear) {
    get_shader().use();
    for (int i = 0; i < instances.size(); i += 1024) {
      ulong size = std::min(1024ull, instances.size() - i);
      get_ubo().data(instances.data(), size, i);
      glBindBufferBase(GL_UNIFORM_BUFFER, 0, get_ubo().handle);
      mod->mesh->idraw(size);
    }
    if (clear) {
      this->clear();
    }
  }

  void InstancedModel::draw_all() {
    Shader prev = GL::shader;
    GL::shader = get_shader();
    for (const auto& it : __imodel_cache) {
      ((InstancedModel*)it.second)->draw(true);
    }
    GL::shader = prev;
  }

  InstancedModel* InstancedModel::get(const std::string& src, const Model::Args& colors) {
    std::string key = combine(src, colors);
    if (__imodel_cache.find(key) == __imodel_cache.end()) {
      __imodel_cache[key] = new InstancedModel(src, colors);
    }
    return __imodel_cache[key];
  }
}