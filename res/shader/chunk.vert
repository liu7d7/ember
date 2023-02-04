#version 450
in vec3 pos;
in vec3 norm;

out vec3 v_pos;
out vec3 v_norm;

uniform mat4 u_proj;
uniform mat4 u_look;

void main() {
  gl_Position = u_proj * u_look * vec4(pos, 1.);
  v_pos = pos;
  v_norm = norm;
}