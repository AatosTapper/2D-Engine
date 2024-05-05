#pragma once

#include "../../config.h"

#include <tuple>

class SpriteComponent;
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
    static void queue_sprite(std::tuple<const SpriteComponent*, glm::mat4> sprite);
    static void draw_sprites();
};
