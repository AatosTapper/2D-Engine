#pragma once

#include "config.h"
#include "engine/rendering/Shader.h"
#include "engine/components/SpriteComponent.h"

#include <tuple>
#include <vector>
#include <memory>

// To access functions, call like this:

// Renderer::instance().init();
// Renderer::instance().queue_sprite(...);

// This class acts like a system for a component type, but it is more integrated to the core gameloop

class Shader;

class Renderer
{
public:
    Renderer();

    void init();
    void start_frame();
    void clear_queues();
    void set_shader(Shader *shader);
    void set_view_proj_matrix(const glm::mat4 &vp_mat);
    void queue_sprite(std::tuple<const SpriteComponent*, glm::mat4> sprite);
    void draw_frame();

private:
    Shader sprite_shader;
    Shader post_process_shader;
    
    Shader *selected_shader;
    glm::mat4 selected_vpm;
    std::vector<std::tuple<const SpriteComponent*, glm::mat4>> sprite_queue;

    uint32_t framebuffer{};
    uint32_t texture_color_buffer{};
    uint32_t rbo{};
    SpriteComponent screen_quad; // a bit stupid but we can access the quad mesh with this

    void create_framebuffer();
    void regenerate_framebuffer();
    void draw_sprites();

public:
    static Renderer &instance()
    {
        static Renderer instance;
        return instance;
    }
};
