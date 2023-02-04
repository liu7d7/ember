#version 450

in vec2 uv;

out vec2 v_uv;

void main() {
    v_uv = uv;
    gl_Position = vec4(uv * 2. - 1., 0., 1.);
}