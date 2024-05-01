#version 410 core 

out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D u_texture;

void main()
{
    frag_color = texture(u_texture, tex_coord);
}