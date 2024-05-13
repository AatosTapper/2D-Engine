#pragma once

#include "config.h"
#include "engine/rendering/Shader.h"
#include "engine/components/SpriteComponent.h"
#include "singleton.h"
#include "Ref.h"

#include <tuple>
#include <vector>
#include <memory>
#include <functional>

// To access functions, call like this:

// Renderer::instance().init();
// Renderer::instance().queue_sprite(...);

// This class acts like a system for a component type, but it is more integrated to the core gameloop

class Shader;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    IMPL_SINGLETON_DISPATCHER(Renderer)

    void init();
    void start_frame();
    void clear_queues();
    void set_shader(Ptr<Shader> shader);
    void set_view_proj_matrix(const glm::mat4 &vp_mat);
    void queue_sprite(std::tuple<Ref<const QuadMesh>, glm::mat4> sprite);
    void draw_frame();

private:
    Shader sprite_shader;
    Shader post_process_shader;
    
    Shader *selected_shader;
    glm::mat4 selected_vpm;
    std::vector<std::tuple<Ref<const QuadMesh>, glm::mat4>> sprite_queue;

    uint32_t framebuffer{};
    uint32_t texture_color_buffer{};
    uint32_t texture_depth_buffer{};
    uint32_t rbo{};
    QuadMesh screen_quad;

    void create_framebuffers();
    void delete_framebuffers();
    void regenerate_framebuffer();
    void draw_sprites();
    void render_framebuffer();
};
