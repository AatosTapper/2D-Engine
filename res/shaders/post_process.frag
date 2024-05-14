#version 410 core
out vec4 frag_color;
in vec2 tex_coord;

uniform sampler2D tex_col;
uniform sampler2D tex_dep;

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

const float near = 0.1;
const float far = 1000.0;
const float fog_density = 0.003;
const vec3 fog_color = vec3(0.92, 0.96, 0.99);

float linearize_depth(float d)
{
    float z_n = 2.0 * d - 1.0;
    return 2.0 * near * far / (far + near - z_n * (far - near));
}

float calc_fog_factor() 
{
    float depth = linearize_depth(texture(tex_dep, tex_coord).r);
    float power = fog_density * depth;
    return 1.0 / exp(power * power);
}

vec4 combine_output()
{
    vec4 col = texture(tex_col, tex_coord);
    return mix(vec4(fog_color, 1.0), col, calc_fog_factor());
}

void main()
{
    frag_color = aces(combine_output());
}