#pragma once

#include "config.h"
#include "rendering/Shader.h"
#include "components/SpriteComponent.h"
#include "singleton.h"
#include "Ref.h"

#include <tuple>
#include <vector>
#include <memory>
#include <functional>

// This class acts like a system for a component type, but it is more integrated to the core gameloop

class Shader;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    IMPL_SINGLETON_DISPATCHER(Renderer)
    IMPL_NO_COPY(Renderer)

    void init();
    void start_frame();
    void clear_queues();
    void set_shader(Ptr<Shader> shader);
    void set_view_proj_matrix(const glm::mat4 &vp_mat);
    void queue_sprite(std::tuple<Ref<const QuadMeshComponent>, glm::mat4> sprite);
    void draw_frame();

private:
    Shader m_sprite_shader;
    Shader m_post_process_shader;
    
    Shader *m_selected_shader = nullptr;
    glm::mat4 m_selected_vpm;
    std::vector<std::tuple<Ref<const QuadMeshComponent>, glm::mat4>> m_sprite_queue;

    uint32_t m_framebuffer = 0;
    uint32_t m_texture_color_buffer = 0;
    uint32_t m_texture_depth_buffer = 0;
    uint32_t m_rbo = 0;
    QuadMeshComponent m_screen_quad;

    void create_framebuffers();
    void delete_framebuffers();
    void regenerate_framebuffer();
    void draw_sprites();
    void render_framebuffer();
};
