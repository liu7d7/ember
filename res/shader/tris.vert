#version 460

in vec3 pos;
in vec4 color;

out vec4 v_color;

uniform mat4 u_look;
uniform mat4 u_proj;

void main() {
  vec4 final = u_proj * u_look * vec4(pos, 1.0);
  gl_Position = final;
  v_color = color;
}