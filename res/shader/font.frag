#version 460

in vec2 v_uv;
in vec4 v_col;

out vec4 color;

uniform sampler2D u_tex;

void main() {
  float r = texture(u_tex, v_uv).r;
  if (r == 0) discard;
  color = vec4(vec3(1.), r) * v_col;
}