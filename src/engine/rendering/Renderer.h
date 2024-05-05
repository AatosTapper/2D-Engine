#pragma once

#include "../../config.h"
#include "Shader.h"

#include <tuple>
#include <vector>
#include <memory>

// To access functions, call like this:

// Renderer::instance().init();
// Renderer::instance().queue_sprite(...);

class SpriteComponent;
class Shader;

class Renderer
{
public:
    Renderer()
      : sprite_shader(std::make_unique<Shader>("../res/shaders/default.vert", "../res/shaders/default.frag")), 
        selected_shader(nullptr) {}

    void init();
    void start_frame();
    void end_frame();
    void set_shader(Shader *shader);
    void set_view_proj_matrix(const glm::mat4 &vp_mat);
    void queue_sprite(std::tuple<const SpriteComponent*, glm::mat4> sprite);
    void draw_sprites();

private:
    std::unique_ptr<Shader> sprite_shader;
    
    Shader *selected_shader;
    glm::mat4 selected_vpm;
    std::vector<std::tuple<const SpriteComponent*, glm::mat4>> sprite_queue;

public:
    static Renderer &instance()
    {
        static Renderer instance;
        return instance;
    }
};
