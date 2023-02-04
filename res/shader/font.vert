#version 460

in vec3 pos;
in vec2 uv;
in vec4 col;

out vec2 v_uv;
out vec4 v_col;

uniform mat4 u_proj;

void main() {
  gl_Position = u_proj * vec4(pos, 1.);
  v_uv = uv;
  v_col = col;
}