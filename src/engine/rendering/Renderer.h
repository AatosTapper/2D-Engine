#pragma once

#include "../../config.h"
#include "Shader.h"

#include <tuple>
#include <vector>
#include <memory>

// To access functions, call like this:

// Renderer::instance().init();
// Renderer::instance().queue_sprite(...);

// This class acts like a system for a component type, but it is more integrated to the core gameloop

class SpriteComponent;
class Shader;

class Renderer
{
public:
    Renderer()
      : sprite_shader(Shader("../res/shaders/sprite.vert", "../res/shaders/sprite.frag")), 
        selected_shader(nullptr) {}

    void init();
    void start_frame();
    void clear_queues();
    void set_shader(Shader *shader);
    void set_view_proj_matrix(const glm::mat4 &vp_mat);
    void queue_sprite(std::tuple<const SpriteComponent*, glm::mat4> sprite);
    void draw_sprites();

private:
    Shader sprite_shader;
    
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
