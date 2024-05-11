#version 410 core
out vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D t0;

/* 
    tonemapping from HDR to SDR
*/
vec4 aces(vec4 x) 
{
    const float a = 2.51;
    const float b = 0.03;
    const float c = 2.43;
    const float d = 0.59;
    const float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

float get_brightness(vec4 col)
{
    return 0.2126 * col.x + 0.7152 * col.y + 0.0722 * col.z;
}

void main()
{
    vec4 col = texture(t0, tex_coord);

    frag_color = aces(col);
}