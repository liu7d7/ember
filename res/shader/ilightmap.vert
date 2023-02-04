#version 460
in vec3 pos;

uniform mat4 u_lightSpace;
layout(binding = 0, packed) uniform u_instanceInfo {
  mat4 model[1024];
};

void main() {
  gl_Position = u_lightSpace * model[gl_InstanceID] * vec4(pos, 1.0);
}