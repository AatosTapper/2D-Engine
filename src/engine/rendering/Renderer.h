#pragma once

#include "../../config.h"

class Sprite;
class Shader;

class Renderer
{
public:
    Renderer() = delete;

    static void init();
    static void start_frame();
    static void end_frame();
    static void set_shader(Shader *shader);
    static void set_view_proj_matrix(const glm::mat4 &vp_mat);
    static void draw_sprite(const Sprite &sprite);
};
