#version 460
in vec3 pos;

uniform mat4 u_lightSpace;
uniform mat4 u_model;

void main() {
    gl_Position = u_lightSpace * u_model * vec4(pos, 1.0);
}