#version 460

layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 color;
layout(location=3) in vec3 shadingModel;

out vec4 v_pos;
out vec3 v_normal;
out vec3 v_color;
out vec3 v_shadingModel;

uniform mat4 u_proj;
uniform mat4 u_look;
uniform mat4 u_lightSpace;
uniform float u_time;

const float PI = 3.1415926535897932384626433832795;

layout(binding = 0, packed) uniform u_instanceInfo {
  mat4 model[1024];
};

void main() {
  mat4 mod = model[gl_InstanceID];
  v_pos = mod * vec4(pos, 1.);
  v_color = color;
  v_shadingModel = shadingModel;
  v_normal = mat3(transpose(inverse(mod))) * normal;
  gl_Position = u_proj * u_look * v_pos;
}