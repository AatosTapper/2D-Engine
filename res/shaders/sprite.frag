#version 410 core 

out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D u_texture_sampler;

void main()
{
    vec4 tex_color = texture(u_texture_sampler, tex_coord);

    if (tex_color.a < 0.1)
        discard;

    frag_color = tex_color;
}