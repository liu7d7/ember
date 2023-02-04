//
// Created by richard may clarkson on 11/12/2022.
//

#ifndef GLENGINE_SHADER_H
#define GLENGINE_SHADER_H

#include "global.h"
#include "gtc/type_ptr.hpp"

namespace Ember {
  struct Shader {
    uint handle;
    std::unordered_map<std::string, int> uniforms;

    Shader();

    Shader(const std::string&, const std::string&);

    Shader(const std::string&, const std::string&, const std::string&);

    inline void array(const std::string& name, uint size) {
      for (uint i = 0; i < size; i++) {
        uniforms[name + "[" + std::to_string(i) + "]"] = glGetUniformLocation(handle,
                                                                         (name + "[" + std::to_string(i) + "]").c_str());
      }
    }

    inline void set_int(const std::string& name, int value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_int: uniform " + name + " not found");
        return;
      }
      glUniform1i(uniforms.at(name), value);
    }

    inline void set_float(const std::string& name, float value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_float: uniform " + name + " not found");
        return;
      }
      glUniform1f(uniforms.at(name), value);
    }

    inline void set_vec2(const std::string& name, const glm::vec2& value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_vec2: uniform " + name + " not found");
        return;
      }
      glUniform2fv(uniforms.at(name), 1, glm::value_ptr(value));
    }

    inline void set_vec3(const std::string& name, const glm::vec3& value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_vec3: uniform " + name + " not found");
        return;
      }
      glUniform3fv(uniforms.at(name), 1, glm::value_ptr(value));
    }

    inline void set_vec4(const std::string& name, const glm::vec4& value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_vec4: uniform " + name + " not found");
        return;
      }
      glUniform4fv(uniforms.at(name), 1, glm::value_ptr(value));
    }

    inline void set_mat2(const std::string& name, const glm::mat2& value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_mat2: uniform " + name + " not found");
        return;
      }
      glUniformMatrix2fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    inline void set_mat3(const std::string& name, const glm::mat3& value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_mat3: uniform " + name + " not found");
        return;
      }
      glUniformMatrix3fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    inline void set_mat4(const std::string& name, const glm::mat4& value, bool isDefault = false) const {
      if (uniforms.find(name) == uniforms.end()) {
        if (!isDefault) die("set_mat4: uniform " + name + " not found");
        return;
      }
      glUniformMatrix4fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    inline void use() const {
      glUseProgram(handle);
    }
  };
}

#endif //GLENGINE_SHADER_H
