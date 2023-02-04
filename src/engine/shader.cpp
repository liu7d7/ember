//
// Created by richard may clarkson on 11/12/2022.
//
#include "engine/shader.h"
#include "gtc/type_ptr.hpp"

namespace Ember {
  uint shader_source(const std::string& src, uint type) {
    std::ifstream file(src);
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    uint out = glCreateShader(type);
    std::string source = stream.str();
    auto buf = source.c_str();
    glShaderSource(out, 1, &buf, nullptr);
    glCompileShader(out);
    int t;
    glGetShaderiv(out, GL_COMPILE_STATUS, &t);
    if (t == GL_TRUE) return out;
    char log[512];
    glGetShaderInfoLog(out, 512, nullptr, log);
    std::string l = log;
    die("compiling (" + src + ") " + gl_to_string(type) + " " + l);
  }

  void do_uniforms(Shader& in) {
    int numUniforms;
    glGetProgramiv(in.handle, GL_ACTIVE_UNIFORMS, &numUniforms);
    in.uniforms = std::unordered_map<std::string, int>();

    for (uint i = 0; i < numUniforms; i++) {
      char* buf = new char[256];
      int len;
      glGetActiveUniform(in.handle, i, 256, &len, nullptr, nullptr, buf);
      int loc = glGetUniformLocation(in.handle, buf);
      std::string str = buf;
      in.uniforms[str] = loc;
      delete[] buf;
    }
  }

  void link_program(Shader& in) {
    glLinkProgram(in.handle);
    int t;
    glGetProgramiv(in.handle, GL_LINK_STATUS, &t);
    if (t == GL_TRUE) return;
    char* buf = new char[256];
    glGetProgramInfoLog(in.handle, 256, nullptr, buf);
    std::string str = buf;
    delete[] buf;
    die("link " + gl_to_string(t) + " " + str);
  }

  Shader::Shader(const std::string& vsrc, const std::string& fsrc) {
    uint vsh = shader_source(vsrc, GL_VERTEX_SHADER);
    uint fsh = shader_source(fsrc, GL_FRAGMENT_SHADER);

    handle = glCreateProgram();
    glAttachShader(handle, vsh);
    glAttachShader(handle, fsh);

    link_program(*this);

    glDetachShader(handle, vsh);
    glDeleteShader(vsh);
    glDetachShader(handle, fsh);
    glDeleteShader(fsh);

    do_uniforms(*this);
  }

  Shader::Shader(const std::string& vsrc, const std::string& fsrc, const std::string& gsrc) {
    uint vsh = shader_source(vsrc, GL_VERTEX_SHADER);
    uint fsh = shader_source(fsrc, GL_FRAGMENT_SHADER);
    uint gsh = shader_source(gsrc, GL_GEOMETRY_SHADER);

    handle = glCreateProgram();
    glAttachShader(handle, vsh);
    glAttachShader(handle, fsh);
    glAttachShader(handle, gsh);

    link_program(*this);

    glDetachShader(handle, vsh);
    glDeleteShader(vsh);
    glDetachShader(handle, fsh);
    glDeleteShader(fsh);
    glDetachShader(handle, gsh);
    glDeleteShader(gsh);

    do_uniforms(*this);
  }

  Shader::Shader() : handle(0) {
  }
}