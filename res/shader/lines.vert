#version 450

layout(location = 0) in vec4 pos_width;
layout(location = 1) in vec4 col;

layout(location = 0) uniform mat4 u_look;
layout(location = 1) uniform mat4 u_proj;
layout(location = 4) uniform mat4 u_model;

out vec4 v_col;
out noperspective float v_line_width;

void main()
{
    v_col = col;
    v_line_width = pos_width.w;
    gl_Position = u_proj * u_look * u_model * vec4(pos_width.xyz, 1.0);
}