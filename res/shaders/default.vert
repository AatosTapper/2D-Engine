#version 410 core 

layout (location = 0) in vec3 i_pos;
layout (location = 1) in vec3 i_col;

out vec3 vert_color;

void main()
{
    vert_color = i_col;
    gl_Position = vec4(i_pos, 1.0);
}