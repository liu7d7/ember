//
// Created by richard may clarkson on 22/12/2022.
//

#ifndef GLENGINE_IMODEL_H
#define GLENGINE_IMODEL_H

#include "global.h"
#include "model.h"

namespace Ember {

  struct InstancedModel {
  private:
    InstancedModel(const std::string& src, Model::Args colors);

  public:
    std::vector<glm::mat4> instances;
    Model* mod;
    bool changed{false};

    static Shader get_shader() {
      static Shader shader;
      if (shader.handle == 0) {
        shader = Shader("res/shader/imodel.vert", "res/shader/imodel.frag");
        shader.array("u_tex", 8);
      }
      return shader;
    }

    static Buffer<glm::mat4> get_ubo() {
      static Buffer<glm::mat4> ubo;
      if (ubo.handle == 0) {
        ubo = Buffer<glm::mat4>(GL_UNIFORM_BUFFER, 1024);
        uint blockIndex = glGetUniformBlockIndex(get_shader().handle, "u_instanceInfo");
        int blockSize;
        glGetActiveUniformBlockiv(get_shader().handle, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
        const char* name[] = {"model"};
        uint* index = new uint();
        glGetUniformIndices(get_shader().handle, 1, name, index);
        ubo.use();
        glBufferData(GL_UNIFORM_BUFFER, blockSize, nullptr, GL_DYNAMIC_DRAW);
      }
      return ubo;
    }

    void add(const glm::vec3& pos, const glm::mat4& other = glm::mat4(1.f));

    void clear();

    void draw(bool clear);

    static std::string combine(const std::string& src, const Model::Args& args) {
      std::stringstream out;
      out << src;
        for (auto& it : args)
          for (auto& [key, value] : it.second)
          out << key << value.x << value.y << value.z << value.w;

      return out.str();
    }

    static InstancedModel* get(const std::string& src, const Model::Args& colors);

    static void draw_all();
  };

  static std::unordered_map<std::string, InstancedModel*> __imodel_cache;
}

#endif //GLENGINE_IMODEL_H
