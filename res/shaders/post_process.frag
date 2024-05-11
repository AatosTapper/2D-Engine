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

float linearize_depth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    vec4 col = texture(tex_col, tex_coord);
    float depth = linearize_depth(texture(tex_dep, tex_coord).r) / far;
    vec4 depth_vec = vec4(vec3(pow(depth, 1.4)), 1.0);

    frag_color = aces(col * (1 - depth_vec) + depth_vec);
}