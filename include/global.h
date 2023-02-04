//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_GLOBAL_H
#define GLENGINE_GLOBAL_H

#include "glm.hpp"
#include "glad.h"
#include "glfw3.h"
#include "iostream"
#include "unordered_map"
#include "vector"
#include "streambuf"
#include "sstream"
#include "fstream"

typedef long double ldouble;
#define uint unsigned int
#define llong long long
#define ulong unsigned llong
#define ubyte unsigned char
#define ushort unsigned short

#define var auto
#define now (float)(glfwGetTime() * 1000)
#define nodiscard [[nodiscard]]
#define noreturn [[noreturn]]

#define instanceof(obj, type) (typeid(obj) == typeid(type))

#define current_palette Palette::DreamyHaze

inline std::string gl_to_string(GLenum en) {
  switch (en) {
    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";
    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";
    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_ARRAY_BUFFER:
      return "GL_ARRAY_BUFFER";
    case GL_ELEMENT_ARRAY_BUFFER:
      return "GL_ELEMENT_ARRAY_BUFFER";
    case GL_STATIC_DRAW:
      return "GL_STATIC_DRAW";
    case GL_DYNAMIC_DRAW:
      return "GL_DYNAMIC_DRAW";
    case GL_STREAM_DRAW:
      return "GL_STREAM_DRAW";
    case GL_FLOAT:
      return "GL_FLOAT";
    case GL_UNSIGNED_INT:
      return "GL_UNSIGNED_INT";
    case GL_UNSIGNED_BYTE:
      return "GL_UNSIGNED_BYTE";
    case GL_TRIANGLES:
      return "GL_TRIANGLES";
    case GL_TRIANGLE_STRIP:
      return "GL_TRIANGLE_STRIP";
    case GL_TRIANGLE_FAN:
      return "GL_TRIANGLE_FAN";
    case GL_POINTS:
      return "GL_POINTS";
    case GL_LINES:
      return "GL_LINES";
    case GL_LINE_STRIP:
      return "GL_LINE_STRIP";
    case GL_LINE_LOOP:
      return "GL_LINE_LOOP";
    case GL_COMPILE_STATUS:
      return "GL_COMPILE_STATUS";
    case GL_FRAGMENT_SHADER:
      return "GL_FRAGMENT_SHADER";
    case GL_VERTEX_SHADER:
      return "GL_VERTEX_SHADER";
    case GL_LINK_STATUS:
      return "GL_LINK_STATUS";
    case GL_TEXTURE_2D:
      return "GL_TEXTURE_2D";
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
    case GL_FRAMEBUFFER_UNSUPPORTED:
      return "GL_FRAMEBUFFER_UNSUPPORTED";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
      return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
    case GL_FRAMEBUFFER_UNDEFINED:
      return "GL_FRAMEBUFFER_UNDEFINED";
    case GL_FRAMEBUFFER_COMPLETE:
      return "GL_FRAMEBUFFER_COMPLETE";
    case GL_TEXTURE_MIN_FILTER:
      return "GL_TEXTURE_MIN_FILTER";
    case GL_TEXTURE_MAG_FILTER:
      return "GL_TEXTURE_MAG_FILTER";
    case GL_TEXTURE_WRAP_S:
      return "GL_TEXTURE_WRAP_S";
    case GL_TEXTURE_WRAP_T:
      return "GL_TEXTURE_WRAP_T";
    case GL_CLAMP_TO_EDGE:
      return "GL_CLAMP_TO_EDGE";
    case GL_LINEAR:
      return "GL_LINEAR";
    case GL_NEAREST:
      return "GL_NEAREST";
    case GL_DEPTH_ATTACHMENT:
      return "GL_DEPTH_ATTACHMENT";
    case GL_DEPTH_COMPONENT:
      return "GL_DEPTH_COMPONENT";
    case GL_DEPTH_COMPONENT16:
      return "GL_DEPTH_COMPONENT16";
    case GL_DEPTH_COMPONENT24:
      return "GL_DEPTH_COMPONENT24";
    default:
      return "UNKNOWN";
  }
}

noreturn inline void die(const std::string& loc) {
  glfwTerminate();
  std::cout << (loc) << '\n';
  exit(1);
}

inline void die_if_gl(const std::string& loc) {
  GLenum error = GL_NO_ERROR;
  error = glGetError();
  if (GL_NO_ERROR != error) {
    std::cout << "die_if_gl: " << gl_to_string(error) << " at " << (loc) << '!' << '\n';
    glfwTerminate();
    exit(1);
  }
}

inline bool approx_eq(float a, float b, float epsilon = 0.0001f) {
  return std::abs(a - b) < epsilon;
}

template<typename T>
struct Array {
  T* ptr;
  llong size;
};

struct HashVec2 {
  template<typename T, glm::qualifier Q>
  size_t operator()(const glm::vec<2, T, Q>& vec) const {
    static std::hash<float> h;
    return h(vec.x) ^ h(vec.y);
  }
};

struct HashTypeInfo {
  size_t operator()(const std::type_info& info) const {
    return info.hash_code();
  }
};

inline float operator "" _rad(ldouble deg) {
  return glm::radians(static_cast<float>(deg));
}

inline float operator "" _deg(ldouble rad) {
  return glm::degrees(static_cast<float>(rad));
}

inline glm::vec4 operator "" _vec4(ulong val) {
  return {
    static_cast<float>((val >> 16) & 0xFF) / 255.0f,
    static_cast<float>((val >> 8) & 0xFF) / 255.0f,
    static_cast<float>(val & 0xFF) / 255.0f,
    static_cast<float>((val >> 24) & 0xFF) / 255.0f
  };
}

inline glm::vec4 to_vec4(uint val) {
  return {
    static_cast<float>((val >> 16) & 0xFF) / 255.0f,
    static_cast<float>((val >> 8) & 0xFF) / 255.0f,
    static_cast<float>(val & 0xFF) / 255.0f,
    static_cast<float>((val >> 24) & 0xFF) / 255.0f
  };
}

inline float length_squared(const glm::vec3& v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline float distance2dSquared(const glm::vec3& a, const glm::vec3& b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template<typename T>
inline T lerp(const T& a, const T& b, float t) {
  return a + (b - a) * t;
}

using Vec2i = glm::vec<2, int, glm::defaultp>;

#endif //GLENGINE_GLOBAL_H
